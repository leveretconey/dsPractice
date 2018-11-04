#pragma once
class Timer
{
public:
	void RecordCurrentTime();
	unsigned int GetTimeSpan();
	void ShowTime();
	Timer();
	~Timer();
protected:
	unsigned int time;
};

