#ifndef __CONST_METHOD_TESTER_H__
#define __CONST_METHOD_TESTER_H__

#include <chrono>
#include <functional>
#include <vector>

#include "./tester_result.hpp"
#include "method_tester_base.hpp"

template <class Result, class T>
class ConstMethodTester : public MethodTesterBase<Result, T>
{
private:
	typedef Result (T::*t_pMemFuncConst)() const;
	t_pMemFuncConst pMemfuncConst;

public:
	ConstMethodTester(t_pMemFuncConst pm) : pMemfuncConst(pm) {}

	const Result operator()(T* pObj) const
	{
		std::cout << "operator () overloaded in const methodtester" << std::endl;
		return (pObj->*pMemfuncConst)();
	}

	TesterResult<Result>* when(void)
	{
		using namespace std::chrono;
		T* tmp;

		this->startTime = steady_clock::now();
		Result result = (tmp->*pMemfuncConst)();
		this->endTime = steady_clock::now();

		return (new TesterResult<Result>(result, this->endTime - this->startTime));
	}
	// template <typename... Args>
	// template <typename T>
	// ConstMethodTester* when(T args)
	// {
	// 	std::cout << "hihi" << std::endl;
	// 	t_pMemFuncConst(args);
	// 	return this;
	// }
};

#endif
