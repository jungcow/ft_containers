#ifndef __TESTER_H__
#define __TESTER_H__

#include <chrono>

template <class TesterType>
class Tester
{
private:
	TesterType* tester;

public:
	Tester() : tester()
	{
		tester = new TesterType();
	}
	~Tester()
	{
		delete tester;
	}

	TesterType* operator->()
	{
		return tester;
	}
};

#endif
