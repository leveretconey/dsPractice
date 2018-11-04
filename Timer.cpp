#include "Timer.h"
#include <Windows.h>
#include <iostream>
#pragma comment( lib,"winmm.lib" )

void Timer::RecordCurrentTime()
{
	time = (unsigned int)timeGetTime();
}

unsigned int Timer::GetTimeSpan()
{
	return (unsigned int)timeGetTime() - time;
}

void Timer::ShowTime()
{
	std::cout << "������һ�μ�ʱ" << GetTimeSpan() << "��" << std::endl;
}

Timer::Timer()
{
	RecordCurrentTime();
}


Timer::~Timer()
{
}
