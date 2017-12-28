// mem_benchmarkdlltest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "mem_benchmarkfuncs.h"
#include "windows.h"
int main()
{
//	double latency;
	double bandwidth;
//	latency =mem_benchmark::mem_latency(1024 * 128, 32);
//	bandwidth = mem_benchmark::mem_bw(1024 * 8, ReaderAVX_fun, 0, 1);
	bandwidth = mem_benchmark::mem_benchmark(mem_benchmark_lat,mem_benchmark_l1,0);
	printf("%f", bandwidth);
	Sleep(500);
    return 0;
}

