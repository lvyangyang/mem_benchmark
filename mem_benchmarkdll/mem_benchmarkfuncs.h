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
	//length_test �����ڴ��С��stride ����ڴ���
	//��ʹͬһ��cache �����ڴ��С�Խ��Ҳ�нϴ�Ӱ�죬strideӰ��Ҳ�ܴ�
	MEM_BENCKMARK_DLL_API double mem_latency(int length_test, int stride);

	//length_test �����ڴ��С,test_func_index���Է�����use_hyperthread �Ƿ�ʹ�ó��̣߳�need_buf2 �Ƿ���Ҫ�ڶ������ڴ棨�ڴ渴�ƣ�
	//L1 ��L2 cache дʹ��writersse,����ʹ��copysse,�����̶߳�L1 cache avx д�͸����и���Ӱ�죩
	//�ڴ�д ����ʹ�� writessebyass��copyssebypass(ʹ��avxʵ�鷢����ֵ������)
	MEM_BENCKMARK_DLL_API double mem_bw(int length_test, int test_func_index, bool use_hyperthread, bool need_buf2);

	MEM_BENCKMARK_DLL_API double mem_benchmark(int bw_lat, int l1_l2_l3_mem, int read_write_copy);

}