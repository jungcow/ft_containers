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
		std::cout << 'hihi' << std::endl;
		return i;
	}
};

TEST(ExampleSuite, Example)
{
	Tester<IteratorTest> iterator_tester;
	typedef std::reverse_iterator<int *> rev_iter;

	std::cout << '\n';

	iterator_tester->given(&A::getInt).when();
	iterator_tester->given(&A::getInt).operator();
	// A a;

	// A.*(*iterator_tester->given(&A::getInt))

			decltype(&rev_iter::base) a;
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
