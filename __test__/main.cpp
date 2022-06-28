#include <gtest/gtest.h>

#include <iostream>

#include "iterator/iterator_test.hpp"
#include "tester.hpp"

class A
{
public:
	static const int i = 3;

	double getInt()
	{
		int k = 0;
		while (k < 50000000)
		{
			k++;
		}
		return k;
	}
};

TEST(ExampleSuite, Example)
{
	Tester<IteratorTest> iterator_tester;
	typedef std::reverse_iterator<int *> rev_iter;

	std::cout << '\n';

	iterator_tester->given(&rev_iter::base)->when();
	iterator_tester->given(&A::getInt)->when();

	int *i;
	if (iterator_tester->given(&rev_iter::base)->when()->then(i))
		std::cout << "pass" << std::endl;
	else
		std::cout << "fail" << std::endl;

	if (iterator_tester->given(&A::getInt)->when()->then(50000000))
		std::cout << "pass" << std::endl;
	else
		std::cout << "fail" << std::endl;
	std::cout << iterator_tester->given(&A::getInt)->when()->info<>() << std::endl;
	std::cout << iterator_tester->given(&A::getInt)->when()->info<MILLISECONDS>() << std::endl;
	std::cout << iterator_tester->given(&A::getInt)->when()->info<MICROSECONDS>() << std::endl;
	std::cout << iterator_tester->given(&A::getInt)->when()->info<NANOSECONDS>() << std::endl;
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
