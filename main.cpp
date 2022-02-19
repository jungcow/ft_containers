#include "iterator.hpp"
#include "vector.hpp"
#include <array>
#include <deque>
#include <forward_list>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

int main(void)
{
	int arr[4] = {1, 2, 3, 4};
	float arr2[4] = {1, 2, 3, 4};
	std::vector<int> v(arr, arr + 4);
	std::vector<float> v2(arr2, arr2 + 4);

	// std::vector<int>::iterator vi = v.begin();
	// std::vector<int>::const_iterator cvi = v.begin();

	// vi = cvi;

	ft::vector<int>::iterator vi;
	// ft::vector<int>::const_iterator cvi = vi;
	ft::vector<int>::iterator vi2;
	ft::vector<int>::const_iterator cvi = vi2;
	// ft::vector<int>::const_iterator cvi;
	// ft::vector<int>::iterator vi = cvi;

	// cvi = vi;

	// std::vector<int>::const_iterator cvi;
	// std::vector<int>::iterator vi = cvi;

	// OtherIter = cvi
	//  cvi = vi;
	//  vi = cvi;
	//  *cvi = 2;
	//  ft::cout << *cvi << std::endl;

	// std::vector<int>::iterator vi2;

	// std::cout << *vi << std::endl;
	// // for (; vi != v.end(); vi++) {
	// // 	std::cout << *vi << std::endl;
	// // 	*vi = *vi + 1;
	// // }

	// std::list<int> list(arr, arr + 4);
	// std::list<int>::iterator li = list.begin();
	// std::cout << *li << std::endl;

	// std::deque<int> deq(arr, arr + 4);
	// std::deque<int>::iterator di = deq.begin();

	// std::vector<const int>::iterator vi2(vi);
	// std::cout << *vi2 << std::endl;

	// ft::vector<int> vec;
	// ft::vector<int>::iterator ftvi;
	// ft::vector<int>::iterator ftvi2;

	// ftvi2 = ftvi;

	return 0;
}