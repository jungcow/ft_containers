#include <gtest/gtest.h>

#include <iostream>

// #include "iterator/iterator_test.hpp"
#include "../iterator/iterator_test.hpp"
#include "tester.hpp"

class A
{
public:
	static const int i = 3;
	int val;

	A()
	{
		val = 1;
	}
	A(int v)
	{
		val = v;
	}

	double getInt()
	{
		int k = 0;
		// while (k < 50000000)
		// {
		// 	k++;
		// 	val++;
		// }
		val++;
		return val;
	}
	int getVal()
	{
		return val;
	}
};

TEST(ExampleSuite, Example)
{
	// Tester<IteratorTest> iterator_tester;
	// typedef std::reverse_iterator<int *> rev_iter;

	// std::cout << '\n';

	// iterator_tester->given(&rev_iter::base)->when();
	// iterator_tester->given(&A::getInt)->when();
	A a(5);
	// double (A::*pa)() = a.getInt;

	auto bound_member_data = std::bind(&A::val, a);  // returns ten_two.a
	std::cout << bound_member_data() << '\n';        // 10

	auto bound_member_fn = std::bind(&A::getInt, a);
	std::cout << bound_member_fn() << std::endl;
	std::cout << a.getVal() << std::endl;

	// iterator_tester->given(A::getInt)->when();

	// int *i;
	// if (iterator_tester->given(&rev_iter::base)->when()->then(i))
	// 	std::cout << "pass" << std::endl;
	// else
	// 	std::cout << "fail" << std::endl;

	// if (iterator_tester->given(&A::getInt)->when()->then(50000000))
	// 	std::cout << "pass" << std::endl;
	// else
	// 	std::cout << "fail" << std::endl;
	// std::cout << iterator_tester->given(&A::getInt)->when()->info<>() << std::endl;
	// std::cout << iterator_tester->given(&A::getInt)->when()->info<MILLISECONDS>() << std::endl;
	// std::cout << iterator_tester->given(&A::getInt)->when()->info<MICROSECONDS>() << std::endl;
	// std::cout << iterator_tester->given(&A::getInt)->when()->info<NANOSECONDS>() << std::endl;
	/**
	 * another usage:
	 * MethodTester<double, A> *mt;
	 * mt = iterator_tester->given(&A::getInt);
	 * (*mt)(&a);
	 */
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
