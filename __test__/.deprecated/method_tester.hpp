#ifndef __TESTER_BASE_H__
#define __TESTER_BASE_H__

#include <chrono>
#include <functional>
#include <vector>

#include "./method_tester_base.hpp"
#include "./tester_result.hpp"

template <class Result, class T>
class MethodTester : public MethodTesterBase<Result, T>
{
private:
	typedef Result (T::*t_pMemFunc)();
	t_pMemFunc pMemfunc;

public:
	MethodTester(t_pMemFunc pm) : pMemfunc(pm) {}

	Result operator()(T* pObj)
	{
		std::cout << "operator () overloaded in methodTester" << std::endl;
		return (pObj->*pMemfunc)();
	}

	TesterResult<Result>* when(void)
	{
		using namespace std::chrono;
		T* tmp;

		this->startTime = steady_clock::now();
		Result result = (tmp->*pMemfunc)();
		this->endTime = steady_clock::now();

		return (new TesterResult<Result>(result, this->endTime - this->startTime));
	}
	// template <typename... Args>
	// template <typename T>
	// MethodTester* when(T args)
	// {
	// 	std::cout << "hihi" << std::endl;
	// 	pMemfunc(args);
	// 	return this;
	// }
};

#endif
