#ifndef __TIME_H
#define __TIME_H

#include <ctime>
#include <chrono>
#include <Windows.h>


static bool g_timer_inited = false;
static double g_freq;

class Time
{
private:
	static double delta;

public:

	/*static double g_freg;
	static bool g_timer_inited;*/
	

	static long getTime()
	{
		return time(NULL) * 1000000000;
	}
	
	static long getRegularTime()
	{
		return time(NULL);
	}

	static double getTimeDouble()
	{
		if (!g_timer_inited)
		{
			LARGE_INTEGER li;
			if (!QueryPerformanceFrequency(&li))
				std::cerr << "QueryPerformanceFrequency failed in timer initialization" << std::endl;

			g_freq = double(li.QuadPart);
			g_timer_inited = true;
		}

		LARGE_INTEGER li;
		if (!QueryPerformanceCounter(&li))
			std::cerr << "QueryPerformanceCounter failed in get time!" << std::endl;

		return double(li.QuadPart) / g_freq;
	}

	static std::chrono::high_resolution_clock::time_point getTimeNanoseconds()
	{
		return std::chrono::high_resolution_clock::now();
	}

	/*static double detDelta()
	{
		return delta;
	}

	static void setDelta(double delta)
	{
		Time::delta = delta;
	}*/

	static long const SECOND = 1000000000;
};

#endif