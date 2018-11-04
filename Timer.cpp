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
	std::cout << "距离上一次计时" << GetTimeSpan() << "秒" << std::endl;
}

Timer::Timer()
{
	RecordCurrentTime();
}


Timer::~Timer()
{
}
