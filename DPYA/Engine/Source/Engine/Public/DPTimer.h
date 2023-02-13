#pragma once

#include <windows.h>

class DPTimer
{
public:
	DPTimer()
	{
		INT64 CountPerSec;
		QueryPerformanceFrequency((LARGE_INTEGER*)&CountPerSec);
		TimeScale = 1.f / (double)CountPerSec;

		QueryPerformanceCounter((LARGE_INTEGER*)&PrevCount);
	}

	~DPTimer() { }

	float GetDeltaTime()
	{
		INT64 PresentCount;
		QueryPerformanceCounter((LARGE_INTEGER*)&PresentCount);

		double DelaTime = (PresentCount - PrevCount) * TimeScale;
		PrevCount = PresentCount;

		return static_cast<float>(DelaTime);
	}

private:
	double TimeScale;
	INT64 PrevCount;
};