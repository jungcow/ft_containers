#ifndef __TESTER_BASE_H__
#define __TESTER_BASE_H__

#include <chrono>
// 	std::chrono::steady_clock::time_point begin;
// 	std::chrono::steady_clock::time_point end;
#include <functional>

template <class Result, class T>
class MemberFunctionTest : public std::unary_function<T*, Result>
{
private:
	typedef Result (T::*t_pMemFunc)();
	t_pMemFunc pMemfunc;

public:
	MemberFunctionTest(Result (T::*pm)()) : pMemfunc(pm) {}
	MemberFunctionTest(Result (T::*pm)() const)
	{
		pMemfunc = const_cast<Result (T::*)()>(pm);
	}
	Result operator()(T* pObj)
	{
		return (pObj->*pMemfunc)();
	}

	// template <typename... Args>
	// template <typename T>
	// MemberFunctionTest* when(T args)
	// {
	// 	std::cout << "hihi" << std::endl;
	// 	pMemfunc(args);
	// 	return this;
	// }
	void when(void)
	{
		std::cout << "hihi" << std::endl;
		(this->*pMemfunc)();
		// return this;
	}

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
