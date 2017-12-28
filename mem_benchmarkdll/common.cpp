#include "stdafx.h"
#include "common.h"
#include "test_routine.h"


void ReaderSSE2(state_t *test_state) 
{
	ReaderSSE2(test_state->buf, test_state->nbytes, test_state->test_iter);
}
void WriterSSE2(state_t *test_state)//L1 cache 写性能，超线程 兼容
{
	WriterSSE2(test_state->buf, test_state->nbytes, test_state->test_iter, 32);
}
void CopySSE(state_t *test_state) //L1 cache 写性能，超线程 兼容
{
	CopySSE(test_state->buf, test_state->buf2, test_state->nbytes, test_state->test_iter);
}
void ReaderAVX(state_t *test_state) 
{
	ReaderAVX(test_state->buf, test_state->nbytes, test_state->test_iter);
}
void WriterAVX(state_t *test_state) 
{
	WriterAVX(test_state->buf, test_state->nbytes, test_state->test_iter, 32);
}

void CopyAVX(state_t *test_state)
{
	CopyAVX(test_state->buf, test_state->buf2,test_state->nbytes,test_state->test_iter);
}

void WriterSSE2_bypass(state_t *test_state) //内存测试专用
{
	WriterSSE2_bypass(test_state->buf, test_state->nbytes, test_state->test_iter, 32);
}
void CopySSE_bypass(state_t *test_state)//内存测试专用
{
	CopySSE_bypass(test_state->buf, test_state->buf2, test_state->nbytes, test_state->test_iter);
}


//	WriterAVX_bypass(test_state->buf, test_state->nbytes, test_state->test_iter, 32);

	

//	Reader(mem_state.buf, mem_state.nbytes, test_state->test_iter);
//	Writer(mem_state.buf, mem_state.nbytes, test_state->test_iter, 32);
//	 RandomReader(mem_state.ptr_to_chunks,mem_state.chunks,test_state->test_iter);