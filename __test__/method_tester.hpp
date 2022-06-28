#ifndef __TESTER_BASE_H__
#define __TESTER_BASE_H__

#include <chrono>
// 	std::chrono::steady_clock::time_point begin;
// 	std::chrono::steady_clock::time_point end;
#include <functional>
#include <vector>

template <class Result, class T>
class MethodTester : public std::unary_function<T*, Result>
{
private:
public:
	typedef Result (T::*t_pMemFunc)();
	typedef Result (T::*t_pMemFuncConst)() const;
	t_pMemFunc pMemfunc;
	t_pMemFuncConst pMemfuncConst;
	MethodTester(t_pMemFunc pm) : pMemfunc(pm) {}
	MethodTester(t_pMemFuncConst pm) : t_pMemFuncConst(pm) {}
	MethodTester() {}

	Result operator()(T* pObj) const
	{
		// std::cout << "operator () overloaded in methodTester" << std::endl;
		return (pObj->*pMemfunc)();
	}

	void when(void)
	{
		T tmp;

		Result result = (tmp.*pMemfunc)();
		std::cout << result << std::endl;
		std::cout << "hihi" << std::endl;
		// return this;
	}
	// template <typename... Args>
	// template <typename T>
	// MethodTester* when(T args)
	// {
	// 	std::cout << "hihi" << std::endl;
	// 	pMemfunc(args);
	// 	return this;
	// }

	bool then(Result (T::*pm)())
	{
		return true;
	}

	bool then(void)
	{
		return true;
	}
};

#endif
