#ifndef __ITERATOR_TEST_H__
#define __ITERATOR_TEST_H__

#include "../method_tester.hpp"

class IteratorTest
{
public:
	/**
	 * method: given(1)
	 *
	 * template argument: Result class, member function in Result class
	 */

	template <class Result, class T>
	MethodTester<Result, T> given(Result (T::*pm)())
	{
		// MethodTester<Result, T>* mft;

		// mft = new MethodTester<Result, T>(pm);
		// return mft;
		return (MethodTester<Result, T>(pm));
	}
	/**
	 * overload: given(2)
	 *
	 * description: member function이 const member function인지 아닌지에 따라 오버로딩 함
	 */
	template <class Result, class T>
	MethodTester<Result, T> given(Result (T::*pm)() const)
	{
		// MethodTester<Result, T>* mft;

		// mft = new MethodTester<Result, T>(pm);
		// return mft;
		return (MethodTester<Result, T>(pm));
	}

	// template <typename... Args>
	// IteratorTest* when(Args... args)
	// {
	// 	std::cout << "hihi" << std::endl;
	// 	mem_func(args...);
	// 	return this;
	// }
};

#endif
