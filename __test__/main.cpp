#include <gtest/gtest.h>

#include <iostream>

#include "iterator/iterator_test.hpp"
#include "tester.hpp"

TEST(ExampleSuite, Example)
{
	Tester<IteratorTest> iterator_tester;
	typedef std::reverse_iterator<int *> rev_iter;

	std::cout << '\n';
	iterator_tester->given(&rev_iter::base)->when();

	decltype(&rev_iter::base) a;
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
