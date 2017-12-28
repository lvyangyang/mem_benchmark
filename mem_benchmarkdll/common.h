#pragma once
#include "mytimer.h"


#define TYPE int
typedef unsigned long iter_t;


typedef struct _state {
	DWORD cpu_mask;
	int cpu_number;
	CStopWatch timer;
	double test_time; //setvalue
	double second_per_step;//set value
	iter_t iter_per_step;//test and exam to get 

	size_t	nbytes;
	bool	need_buf2;
	TYPE	*buf;
	TYPE	*buf2;

	iter_t test_iter;//out put
	double test_duration;//output

	HANDLE hevent1;
	HANDLE hevent2;

	bool use_hyperthread;
	size_t hyperthread_multip;

} state_t;

typedef void(*pfunc)(state_t *);

void ReaderSSE2(state_t *test_state);
void WriterSSE2(state_t *test_state);//L1 超线程 兼容;
void CopySSE(state_t *test_state); //L1 超线程 兼容
void WriterSSE2_bypass(state_t *test_state); //内存测试专用
void CopySSE_bypass(state_t *test_state);//内存测试专用

void ReaderAVX(state_t *test_state);
void WriterAVX(state_t *test_state);
void CopyAVX(state_t *test_state);
