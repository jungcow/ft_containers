#ifndef __ITERATOR_TEST_H__
#define __ITERATOR_TEST_H__

#include "../tester_base.hpp"

class IteratorTest
{
public:
	/**
	 * method: given(1)
	 *
	 * template argument: Result class, member function in Result class
	 */

	template <class Result, class T>
	MemberFunctionTest<Result, T>* given(Result (T::*pm)())
	{
		MemberFunctionTest<Result, T>* mft;

		mft = new MemberFunctionTest<Result, T>(pm);
		return mft;
	}
	/**
	 * overload: given(2)
	 *
	 * description: member function이 const member function인지 아닌지에 따라 오버로딩 함
	 */
	template <class Result, class T>
	MemberFunctionTest<Result, T>* given(Result (T::*pm)() const)
	{
		MemberFunctionTest<Result, T>* mft;

		mft = new MemberFunctionTest<Result, T>(pm);
		return mft;
	}

	template <typename... Args>
	IteratorTest* when(Args... args)
	{
		std::cout << "hihi" << std::endl;
		mem_func(args...);
		return this;
	}
};

#endif
