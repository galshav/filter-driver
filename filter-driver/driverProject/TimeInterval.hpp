#pragma once
#include <ntddk.h>

#ifdef DBG
#define CALCULATE_TIME_INTERVAL() TimeInterval timeInterval
#else
#define CALCULATE_TIME_INTERVAL()
#endif

class TimeInterval
{
public:
	TimeInterval(const TimeInterval& other) = delete;
	TimeInterval(TimeInterval&& other) = delete;
	TimeInterval& operator=(const TimeInterval& other) = delete;
	TimeInterval& operator=(TimeInterval&& other) = delete;
	TimeInterval()
	{
		m_BeginTime = KeQueryPerformanceCounter(&m_EndTime);
	}

	~TimeInterval()
	{
		m_EndTime = KeQueryPerformanceCounter(NULL);
		auto elapsedTime = m_BeginTime.QuadPart - m_EndTime.QuadPart;
		elapsedTime *= 1000000;
		elapsedTime /= m_Resolution.QuadPart;
		KdPrint(("Time interval: %lld\r\n", elapsedTime));
	}

private:
	LARGE_INTEGER m_BeginTime{ 0 };
	LARGE_INTEGER m_EndTime{ 0 };
	LARGE_INTEGER m_Resolution{ 0 };
};