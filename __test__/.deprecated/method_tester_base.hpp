#ifndef __METHOD_TESTER_BASE_H__
#define __METHOD_TESTER_BASE_H__

#include <chrono>
#include <functional>
#include <vector>

template <class Result, class T>
class MethodTesterBase : public std::unary_function<T*, Result>
{
protected:
	std::chrono::steady_clock::time_point startTime;
	std::chrono::steady_clock::time_point endTime;

public:
	void operator()(void) const
	{
		std::cout << "\noperator () overloaded in methodTester" << std::endl;
	}
};

#endif