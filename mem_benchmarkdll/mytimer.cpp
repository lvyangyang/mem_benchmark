#include "stdafx.h"
#include "mytimer.h"
CStopWatch::CStopWatch()
{
	m_start.QuadPart = 0;
	m_stop.QuadPart = 0;
	QueryPerformanceFrequency(&m_frequency);
}

void CStopWatch::start()
{
	QueryPerformanceCounter(&m_start);
}

void CStopWatch::stop()
{
	QueryPerformanceCounter(&m_stop);
}

double CStopWatch::getElapsedTime()
{
	LARGE_INTEGER time;
	time.QuadPart = m_stop.QuadPart - m_start.QuadPart;
	return (double)time.QuadPart / (double)m_frequency.QuadPart;
}
