// mem_benchmarkdll.cpp : 定义 DLL 应用程序的导出函数。
//


#include "stdafx.h"

#include "mem_benchmarkfuncs.h"


#include "windows.h"
#include "test_routine.h"
#include <vector>
#include <concrtrm.h>
#include "mytimer.h"
#include "processorinfo.h"
#include "common.h"
#include <algorithm>
#define TYPE int
using namespace std;
namespace mem_benchmark {
	typedef unsigned long iter_t;

	typedef struct test_info {
		state_t test_state;
		pfunc test_func;
	}testinfo;

	void init_loop(void *cookie)
	{
		state_t *state = (state_t *)cookie;

		state->buf = (TYPE *)VirtualAlloc(NULL, state->nbytes, MEM_COMMIT, PAGE_READWRITE);
		if (!state->buf) {
			perror("malloc");
			return;
		}
		memset((void*)state->buf, 0, state->nbytes);

		if (state->need_buf2 == 1) {
			state->buf2 = (TYPE *)VirtualAlloc(NULL, state->nbytes, MEM_COMMIT, PAGE_READWRITE);
			if (!state->buf2) {
				perror("malloc");
				return;
			}
			memset((void*)state->buf, 0, state->nbytes);

		}
	}

	void cleanup(void *cookie)
	{
		state_t *state = (state_t *)cookie;
		VirtualFree(state->buf, state->nbytes, MEM_DECOMMIT);
		if (state->need_buf2) VirtualFree(state->buf2, state->nbytes, MEM_DECOMMIT);
	}

	DWORD WINAPI thread_mem_test(LPVOID lparam)
	{

		double duration = 0;
		testinfo *test_param = (testinfo *)lparam;
		test_param->test_state.test_iter = 1;
		if (!test_param->test_state.use_hyperthread)
		{
			if ((test_param->test_state.cpu_number + 1) % test_param->test_state.hyperthread_multip != 0)
			{
				test_param->test_state.test_iter = 0;
				SetEvent(test_param->test_state.hevent1);
				return 15;
			}
		}
		CStopWatch timer;
		double second_per_step = 0.1;
		iter_t iter_per_step;
		init_loop(&(test_param->test_state));
		SetThreadAffinityMask(GetCurrentThread(), test_param->test_state.cpu_mask);

		SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
		//等待估计时间
		while (test_param->test_state.timer.getElapsedTime() < 0.1)
			test_param->test_state.timer.stop();
		//估计测试时间
		while (TRUE)
		{

			test_param->test_state.test_iter = test_param->test_state.test_iter * 2;

			timer.start();
			(*test_param->test_func)(&test_param->test_state);//测试函数
			timer.stop();

			duration = timer.getElapsedTime();

			if (duration > 0.5)
			{
				iter_per_step = (double)test_param->test_state.test_iter / duration * second_per_step;
				break;

			}
		}

		test_param->test_state.test_iter = test_param->test_state.test_time / test_param->test_state.second_per_step*iter_per_step;
		//通知估计时间过程结束
		SetEvent(test_param->test_state.hevent1);
		//等待正式测试
		WaitForSingleObject(test_param->test_state.hevent2, INFINITE);
		while (test_param->test_state.timer.getElapsedTime() < 0.1)
			test_param->test_state.timer.stop();
		//	ReaderAVX(test_state->buf, test_state->nbytes, 2);//预先cache缓存

		timer.start();
		(*test_param->test_func)(&test_param->test_state);//测试函数
		timer.stop();

		test_param->test_state.test_duration = timer.getElapsedTime();
		cleanup(&(test_param->test_state));
		return 23;
	}

	pfunc select_test_fun(int i)
	{
		pfunc tempfun;
		switch (i)
		{
		case ReaderSSE2_fun: tempfun = ReaderSSE2; break;
		case WriterSSE2_fun: tempfun = WriterSSE2; break;
		case WriterSSE2_bypass_fun: tempfun = WriterSSE2_bypass; break;
		case CopySSE_bypass_fun: tempfun = CopySSE_bypass; break;
		case ReaderAVX_fun: tempfun = ReaderAVX; break;
		case WriterAVX_fun: tempfun = WriterAVX; break;
		case CopyAVX_fun: tempfun = CopyAVX; break;
		case CopySSE_fun:tempfun = CopySSE; break;
		default:tempfun = NULL; break;
		}
		return tempfun;
	}

	//length_test 测试内存大小，stride随机内存跨度
	//即使同一级cache 测试内存大小对结果也有较大影响，stride影响也很大
	double mem_latency(int length_test, int stride)
	{
		//	TYPE length_test=1024*1024*3.5;
		//	int stride = 4;
		TYPE * ptr_begin;
		int i = 0;
		int access_times = length_test / stride;
		double latency;
		iter_t iter = 1;
		CStopWatch timer;
		double duration;
		ptr_begin = (TYPE *)VirtualAlloc(NULL, length_test + 512, MEM_COMMIT, PAGE_READWRITE);
		memset(ptr_begin, 0, length_test);
		vector<int> rand_ptr;

		int temp_ptr = (int)ptr_begin;
		while ((int)temp_ptr < (int)ptr_begin + length_test)
		{
			temp_ptr = temp_ptr + stride;
			rand_ptr.push_back(temp_ptr);

		}

		random_shuffle(rand_ptr.begin(), rand_ptr.end());

		*ptr_begin = rand_ptr.at(0);
		while (i < access_times - 1)
		{
			*(int *)rand_ptr.at(i) = rand_ptr.at(i + 1);
			i++;
		}

		SetThreadAffinityMask(GetCurrentThread(), 1);
		while (TRUE)
		{
			iter = iter * 2;
			timer.start();
			RandomAccess(ptr_begin, access_times, iter);
			timer.stop();
			duration = timer.getElapsedTime();
			if (duration > 1)
				break;
		}
		latency = duration / access_times / iter;
		VirtualFree(ptr_begin, length_test + 512, MEM_DECOMMIT);
		//Sleep(500);
		return latency;
	}

	//length_test 测试内存大小,test_func_index测试方法，是否使用超线程，是否需要第二个块内存（内存复制）
	//L1 ，L2 cache 写使用writersse,复制使用copysse,（超线程对L1 cache avx 写和复制有负面影响）
	//内存写 复制使用 writessebyass和copyssebypass(使用avx实验发现数值不正常)
	double mem_bw(int length_test, int test_func_index, bool use_hyperthread, bool need_buf2)
	{
		HANDLE hevent1[64];
		HANDLE hevent2[64];
		pfunc test_function;
		int test_function_index;
		double totalspeed = 0;
		UINT64 avg_iter = 0;
		CStopWatch timer;
		testinfo set_test_param;
		processorinfo thisprocessorinfo;
		getprocessorinfo(thisprocessorinfo);

		//*****************参数设置******************************************

		set_test_param.test_state.nbytes = length_test;
		set_test_param.test_state.need_buf2 = need_buf2;
		test_function_index = test_func_index;
		set_test_param.test_state.use_hyperthread = use_hyperthread;

		set_test_param.test_state.second_per_step = 0.1;
		set_test_param.test_state.test_time = 1.5;
		//***********************************************

		//自适应参数调节
		set_test_param.test_state.hyperthread_multip = thisprocessorinfo.logicalProcessorCount / thisprocessorinfo.processorCoreCount;
		if (thisprocessorinfo.logicalProcessorCount == thisprocessorinfo.processorCoreCount)
			set_test_param.test_state.use_hyperthread = 1;
		test_function = select_test_fun(test_function_index);
		if (test_function == NULL) { printf("wrong test function\n"); return 0; }
		set_test_param.test_func = test_function;


		LARGE_INTEGER multi_start_time;
		QueryPerformanceCounter(&multi_start_time);

		vector<testinfo> v_multi_thread_state;
		HANDLE hthread[64];

		int processor_count = thisprocessorinfo.logicalProcessorCount;
		//准备多线程参数
		for (size_t i = 0; i < processor_count; i++)
		{
			testinfo temp_info;
			temp_info = set_test_param;

			temp_info.test_state.cpu_number = i;
			temp_info.test_state.cpu_mask = (DWORD)1 << i;

			temp_info.test_state.timer.m_start = multi_start_time;
			hevent1[i] = temp_info.test_state.hevent1 = CreateEvent(NULL, FALSE, FALSE, NULL);
			hevent2[i] = temp_info.test_state.hevent2 = CreateEvent(NULL, FALSE, FALSE, NULL);

			v_multi_thread_state.push_back(temp_info);

		}
		//创建线程
		for (size_t i = 0; i < processor_count; i++)
		{
			hthread[i] = CreateThread(NULL, NULL, thread_mem_test, &v_multi_thread_state.at(i), 0, NULL);

		}
		//等待估计时间过程结束
		WaitForMultipleObjects(processor_count, hevent1, TRUE, INFINITE);
		for (size_t i = 0; i < processor_count; i++)
		{
			avg_iter += v_multi_thread_state.at(i).test_state.test_iter;
		}
		if (set_test_param.test_state.use_hyperthread == 0)
			avg_iter = avg_iter / thisprocessorinfo.processorCoreCount;
		else
		{
			avg_iter = avg_iter / thisprocessorinfo.logicalProcessorCount;
		}

		//重新设立时间基点
		QueryPerformanceCounter(&multi_start_time);
		//通知准备正式测试
		for (size_t i = 0; i < processor_count; i++)
		{
			v_multi_thread_state.at(i).test_state.timer.m_start = multi_start_time;
			v_multi_thread_state.at(i).test_state.test_iter = avg_iter;
			SetEvent(hevent2[i]);

		}


		//等待测试结束
		WaitForMultipleObjects(processor_count, hthread, TRUE, INFINITE);
		//计算所有线程速度和
		for (size_t i = 0; i < processor_count; i++)
		{

			totalspeed = totalspeed + (double)v_multi_thread_state.at(i).test_state.nbytes*(double)v_multi_thread_state.at(i).test_state.test_iter / (1024 * 1024 * 1024) / v_multi_thread_state.at(i).test_state.test_duration;

		}
		printf("mem read speed %f\n", totalspeed);

		//	Sleep(3000);
		return totalspeed;
	}

	double mem_benchmark(int bw_lat,int l1_l2_l3_mem,int read_write_copy )
	{
		double return_value;
		processorinfo thisprocessorinfo;
		getprocessorinfo(thisprocessorinfo);
		switch (bw_lat)
		{
		case mem_benchmark_bw:
			switch (l1_l2_l3_mem)
			{
			case mem_benchmark_l1:
				switch (read_write_copy)
				{
				case mem_benchmark_read:
					return_value = mem_bw(thisprocessorinfo.processorL1Cachesize/thisprocessorinfo.logicalProcessorCount/2/1024*1024,ReaderAVX_fun,1,0);
					break;
				case mem_benchmark_write:
					if(thisprocessorinfo.logicalProcessorCount>thisprocessorinfo.processorCoreCount)
					return_value = mem_bw(thisprocessorinfo.processorL1Cachesize / thisprocessorinfo.logicalProcessorCount / 2 / 1024 * 1024, WriterSSE2_fun, 1, 0);
					else
					{
						return_value = mem_bw(thisprocessorinfo.processorL1Cachesize / thisprocessorinfo.logicalProcessorCount / 2 / 1024 * 1024, WriterAVX_fun, 1, 0);
					}
					break;
				case mem_benchmark_copy:
					if (thisprocessorinfo.logicalProcessorCount>thisprocessorinfo.processorCoreCount)
					return_value = mem_bw(thisprocessorinfo.processorL1Cachesize / thisprocessorinfo.logicalProcessorCount / 2 / 1024 * 1024, CopySSE_fun, 1, 1);
					else
					{
						return_value = mem_bw(thisprocessorinfo.processorL1Cachesize / thisprocessorinfo.logicalProcessorCount / 3 / 1024 * 1024, CopyAVX_fun, 1, 1);
					}
					break;
				default:
					break;
				}
				break;
			case mem_benchmark_l2:
				switch (read_write_copy)
				{
				case mem_benchmark_read:
					return_value = mem_bw(thisprocessorinfo.processorL2Cachesize / thisprocessorinfo.logicalProcessorCount / 2 / 1024 * 1024, ReaderSSE2_fun, 1, 0);
					break;
				case mem_benchmark_write:
					return_value = mem_bw(thisprocessorinfo.processorL2Cachesize / thisprocessorinfo.logicalProcessorCount / 2 / 1024 * 1024, WriterSSE2_fun, 1, 0);
					break;
				case mem_benchmark_copy:
					return_value = mem_bw(thisprocessorinfo.processorL2Cachesize / thisprocessorinfo.logicalProcessorCount / 3 / 1024 * 1024, CopySSE_fun, 1, 1);
					break;
				default:
					break;
				}
				break;
			case mem_benchmark_l3:
				switch (read_write_copy)
				{
				case mem_benchmark_read:
					return_value = mem_bw(thisprocessorinfo.processorL3Cachesize / thisprocessorinfo.logicalProcessorCount / 2 / 1024 * 1024, ReaderSSE2_fun, 1, 0);
					break;
				case mem_benchmark_write:
					return_value = mem_bw(thisprocessorinfo.processorL3Cachesize / thisprocessorinfo.logicalProcessorCount / 2 / 1024 * 1024, WriterSSE2_fun, 1, 0);
					break;
				case mem_benchmark_copy:
					return_value = mem_bw(thisprocessorinfo.processorL3Cachesize / thisprocessorinfo.logicalProcessorCount / 4 / 1024 * 1024, CopySSE_fun, 1, 1);
					break;
				default:
					break;
				}
				break;
			case mem_benchmark_ram:
				switch (read_write_copy)
				{
				case mem_benchmark_read:
					return_value = mem_bw(thisprocessorinfo.processorL3Cachesize / thisprocessorinfo.processorL3CacheCount* 2 / 1024 * 1024, ReaderAVX_fun, 1, 0);
					break;
				case mem_benchmark_write:
					return_value = mem_bw(thisprocessorinfo.processorL3Cachesize / thisprocessorinfo.processorL3CacheCount * 2 / 1024 * 1024, WriterSSE2_bypass_fun, 1, 0);
					break;
				case mem_benchmark_copy:
					return_value = mem_bw(thisprocessorinfo.processorL3Cachesize / thisprocessorinfo.processorL3CacheCount * 2 / 1024 * 1024, CopySSE_bypass_fun, 1, 1);
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
			break;

		case mem_benchmark_lat:
			switch (l1_l2_l3_mem)
			{
			case mem_benchmark_l1:
				return_value = mem_latency(thisprocessorinfo.processorL1Cachesize / thisprocessorinfo.processorCoreCount*0.8 / 1024 * 1024, 128);

				break;

			case mem_benchmark_l2:

				return_value = mem_latency(thisprocessorinfo.processorL2Cachesize / thisprocessorinfo.processorCoreCount*0.8 / 1024 * 1024, 128);

				break;
			case mem_benchmark_l3:
				return_value = mem_latency(thisprocessorinfo.processorL3Cachesize / thisprocessorinfo.processorCoreCount*0.8 / 1024 * 1024, 128);
				break;
			case mem_benchmark_ram:
				return_value = mem_latency(thisprocessorinfo.processorL3Cachesize / thisprocessorinfo.processorL3CacheCount*5 / 1024 * 1024, 128);
				break;
			default:
				break;
			}
			break;
		default:
			return_value = 0; break;
		}
		return return_value;
	
	}

}//namespace end
/*
int main()
{
	double latency;
	double bandwidth;
	latency = mem_latency(1024 * 128, 32);
	//	bandwidth = mem_bw(1024 * 8, ReaderAVX_fun, 0, 1);
	Sleep(500);
}

*/
