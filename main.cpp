#include <iostream>
#include <vector>

using namespace std;

#include <iostream>  // std::cout
#include <iterator>  // std::reverse_iterator
#include <type_traits>
#include <vector>  // std::vector

#include "algorithm.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"
#include "vector.hpp"

// a case-insensitive comparison function:
bool mycomp(char c1, char c2)
{
	return std::tolower(c1) < std::tolower(c2);
}

struct inputclass : public ft::input_iterator_tag
{
	int a;

	bool operator!=(const inputclass &other)
	{
		return (this != &other);
	}
	int getA()
	{
		return a;
	}
};
struct A
{
	void fn(){};
};

int main(void)
{
	std::vector<int> vec(30, 30);
	std::vector<std::vector<int> > vv(2, vec);
	ft::vector<int>::iterator vi;
	// std::vector<std::vector<int> >::const_iterator vic = vv.begin();

	std::vector<int>::iterator ii;
	++(++ii);
	ii++;
	*ii++;

	ii + 3 + 4;

	std::vector<int>::iterator ii2 = 3 + ii;

	std::cout << boolalpha;
	std::cout << (ii2 > ii) << std::endl;

	int arr[] = {1, 2, 3, 4};
	std::vector<int>::iterator ii3;

	ii2 = ii3 += 6;
	{
		// is_base_of 테스트
		std::cout << ft::is_base_of<ft::input_iterator_tag, ft::forward_iterator_tag>::value << std::endl;
		std::cout << ft::is_arithmetic<float>::value << std::endl;
		std::cout << ft::is_arithmetic<double>::value << std::endl;
		std::cout << ft::is_arithmetic<long double>::value << std::endl;
		std::cout << ft::is_arithmetic<short>::value << std::endl;
		std::cout << ft::is_arithmetic<int>::value << std::endl;
		std::cout << ft::is_integral<char>::value << std::endl;
		std::cout << ft::is_arithmetic<int *>::value << std::endl;
		std::cout << ft::is_arithmetic<int &>::value << std::endl;
		std::cout << ft::is_arithmetic<inputclass>::value << std::endl;
		std::cout << ft::is_array<int[]>::value << std::endl;
		std::cout << ft::is_array<double[]>::value << std::endl;
		std::cout << ft::is_array<int *[]>::value << std::endl;
		std::cout << ft::is_array<int *>::value << std::endl;
	}
	ft::vector<int> vi2(3l, 4);
	ft::vector<int> vi3(arr, arr + 4);

	{
		ft::vector<int> vec6(arr, arr + 4);
		ft::vector<int>::iterator consvi = vec6.begin();

		std::vector<int> vec7(arr, arr + 4);
		int pushi = 9;
		vec7.push_back(pushi);
		pushi++;
		std::cout << *(vec7.end() - 1) << std::endl;

		ft::vector<int> vec8(arr, arr + 4);
		vec8.push_back(pushi);
		pushi++;
		std::cout << *(vec8.end() - 1) << std::endl;

		ft::vector<int> vec9(10, 10);
		ft::vector<int> vec10 = vec9;
	}
	{
		ft::vector<int> vec7(arr, arr + 4);
		ft::vector<int>::iterator vec7i = vec7.begin();
		for (int i = 0; i < 4; i++)
			std::cout << vec7i[i] << std::endl;
	}

	{
		std::vector<int> vec8(1000, 10);
		std::vector<int> vec7(3, 12);

		vec8 = vec7;
		for (size_t i = 0; i < vec8.size(); i++)
		{
			std::cout << vec8[i] << std::endl;
		}
		std::cout << "capacity: " << vec8.capacity() << std::endl;
	}
	{
		std::vector<int> vec7(arr, arr + 4);
		std::reverse_iterator<std::vector<int>::iterator> rvi(vec7.begin());
		rvi.base();

		vec7.clear();
		std::cout << vec7.size() << std::endl;
		std::cout << vec7.capacity() << std::endl;
	}
	{
		ft::vector<int> foo(3, 100);  // three ints with a value of 100
		ft::vector<int> bar(5, 200);  // five ints with a value of 200

		std::cout << &foo[0] << std::endl;
		std::cout << &bar[0] << std::endl;
		foo.swap(bar);
		std::cout << &foo[0] << std::endl;
		std::cout << &bar[0] << std::endl;

		std::cout << "foo contains:";
		for (unsigned i = 0; i < foo.size(); i++)
			std::cout << ' ' << foo[i];
		std::cout << '\n';

		std::cout << "bar contains:";
		for (unsigned i = 0; i < bar.size(); i++)
			std::cout << ' ' << bar[i];
		std::cout << '\n';

		return 0;
	}
	return (0);
}
