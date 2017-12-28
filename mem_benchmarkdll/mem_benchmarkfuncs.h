#pragma once
#define MEM_BENCKMARK_DLL_API __declspec(dllexport) 

#define ReaderSSE2_fun 10
#define WriterSSE2_fun 11
#define CopySSE_fun   12
#define WriterSSE2_bypass_fun 13
#define CopySSE_bypass_fun 14
#define ReaderAVX_fun 20
#define WriterAVX_fun 21
#define CopyAVX_fun 22

#define mem_benchmark_bw 10
#define mem_benchmark_lat 11
#define mem_benchmark_l1 20
#define mem_benchmark_l2 21
#define mem_benchmark_l3 22
#define mem_benchmark_ram 23
#define mem_benchmark_read 30
#define mem_benchmark_write 31
#define mem_benchmark_copy  32



namespace mem_benchmark
{
	//length_test 测试内存大小，stride 随机内存跨度
	//即使同一级cache 测试内存大小对结果也有较大影响，stride影响也很大
	MEM_BENCKMARK_DLL_API double mem_latency(int length_test, int stride);

	//length_test 测试内存大小,test_func_index测试方法，use_hyperthread 是否使用超线程，need_buf2 是否需要第二个块内存（内存复制）
	//L1 ，L2 cache 写使用writersse,复制使用copysse,（超线程对L1 cache avx 写和复制有负面影响）
	//内存写 复制使用 writessebyass和copyssebypass(使用avx实验发现数值不正常)
	MEM_BENCKMARK_DLL_API double mem_bw(int length_test, int test_func_index, bool use_hyperthread, bool need_buf2);

	MEM_BENCKMARK_DLL_API double mem_benchmark(int bw_lat, int l1_l2_l3_mem, int read_write_copy);

}