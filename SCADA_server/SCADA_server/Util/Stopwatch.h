#pragma once
#ifndef STOPWATCH_H
#include "stdafx.h"
template<typename TimeT = std::chrono::seconds,
	typename ClockT = std::chrono::high_resolution_clock,
	typename DurationT = double>
	class Stopwatch
{
private:
	std::chrono::time_point<ClockT> _start, _end;
public:
	Stopwatch() { start(); }
	void start() { _start = _end = ClockT::now(); }
	DurationT stop() { _end = ClockT::now(); return elapsed(); }
	DurationT elapsed() {
		auto delta = std::chrono::duration_cast<TimeT>(_end - _start);
		return delta.count();
	}
	DurationT timePassed() {
		stop();
		auto delta = std::chrono::duration_cast<TimeT>(_end - _start);
		start();
		return delta.count();
	}
};
#define STOPWATCH_H
#endif // !STOPWATCH_H

