

#include <array>
#include <cstdlib>
#include <deque>
#include <forward_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#include "iterator.hpp"
#include "vector.hpp"

class A
{
public:
	int *a;
	A()
	{
		a = new int(4);
		for (int i = 0; i < 4; i++)
		{
			a[i] = i;
		}
	};
};

std::ostream &operator<<(std::ostream &out, A &asdf)
{
	for (int i = 0; i < 4; i++)
	{
		out << asdf.a[i] << " ";
	}
	out << "\n";
	return out;
}

int main(void)
{
	int arr[4] = {1, 2, 3, 4};

	std::cout << "[ vector ]\n\n";
	{
		std::vector<int> vec;
		std::vector<int>::iterator vi = vec.begin();

		vec.insert(vi, 10, 2);
		for (size_t i = 0; i < vec.size(); i++)
		{
			std::cout << vec[i] << " ";
		}
		std::cout << vec.capacity();
	}

	std::cout << "\n[ erase ]\n\n";
	{
		A *Aarr = new A[5];
		std::vector<A> vec(Aarr, Aarr + 4);
		std::vector<A>::iterator veci = vec.begin();

		ft::vector<A> vecft(Aarr, Aarr + 4);
		ft::vector<A>::iterator vecfti = vecft.begin();
		vec.erase(veci + 1, veci + 3);
		vecft.erase(vecfti + 1, vecfti + 3);
		for (int i = 0; i < 4; i++)
		{
			std::cout << &vec[i] << " ";
		}
		std::cout << std::endl;
		for (int i = 0; i < 4; i++)
		{
			std::cout << &vecft[i] << " ";
		}
	}
	system("leaks a.out");

	return 0;
}