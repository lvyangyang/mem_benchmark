#pragma once
#define MEM_BENCKMARK_DLL_API __declspec(dllexport) 
namespace mem_benchmark
{
	MEM_BENCKMARK_DLL_API double mem_latency(int length_test, int stride);
	MEM_BENCKMARK_DLL_API double mem_bw(int length_test, int test_func_index, bool use_hyperthread, bool need_buf2);


}