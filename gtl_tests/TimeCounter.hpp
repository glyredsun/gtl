#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#ifndef _TIMECOUNTER_HPP_

#include <chrono>
class TimeCounter
{
public:
	using system_clock = std::chrono::system_clock;
	using time_point = system_clock::time_point;

	TimeCounter()
	{
		reset();
	}

	void reset()
	{
		begin = system_clock::now();
	}

	double count()
	{
		auto d = system_clock::now() - begin;
		return std::chrono::duration <double, std::ratio<1, 1>>(d).count();
	}

private:
	time_point begin;
};

#endif // !_TIMECOUNTER_HPP_