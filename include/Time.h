#ifndef __TIME_H
#define __TIME_H

#include <ctime>
#include <chrono>

class Time
{
private:
	static double delta;

public:
	static long getTime()
	{
		return time(NULL) * 1000000000;
	}
	
	static long getRegularTime()
	{
		return time(NULL);
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