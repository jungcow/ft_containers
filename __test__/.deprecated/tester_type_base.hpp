#ifndef __TESTER_TYPE_BASE_H__
#define __TESTER_TYPE_BASE_H__

#include "const_method_tester.hpp"
#include "method_tester.hpp"

#if 0
class TesterTypeBase
{
public:
	/**
	 * method: given(1)
	 *
	 * template argument: Result class, member function in Result class
	 */
	template <class Result, class T>
	MethodTester<Result, T>* given(Result (T::*pm)())
	{
		return (new MethodTester<Result, T>(pm));
	}
	/**
	 * overload: given(2)
	 *
	 * description: member function이 const member function인지 아닌지에 따라 오버로딩 함
	 */
	template <class Result, class T>
	ConstMethodTester<Result, T>* given(Result (T::*pm)() const)
	{
		return (new ConstMethodTester<Result, T>(pm));
	}
};
#endif

#endif