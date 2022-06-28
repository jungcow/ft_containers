#ifndef __TESTER_H__
#define __TESTER_H__

#include <chrono>

template <class TesterType>
class Tester
{
private:
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;

	TesterType* tester;

public:
	Tester() : tester()
	{
		tester = new TesterType();
	}

	TesterType* operator->()
	{
		return tester;
	}
};

#endif
