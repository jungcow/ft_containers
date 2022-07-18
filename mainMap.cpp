#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>

#include "map.hpp"
#include "tree/node.hpp"
#include "tree/rb_balance.hpp"
#include "tree/tree.hpp"
#include "type.hpp"
#include "utility.hpp"

typedef ft::pair<char, int> pair;
typedef ft::pair<char, int>* ppair;

template <class Key,
		  class T,
		  class Compare,
		  class Alloc>
class value_compare : public std::binary_function<pair, pair, bool>
{
private:
	friend class map;

public:
	bool operator()(const pair& lhs, const pair& rhs) const
	{
		return comp(lhs.first, rhs.first);
	}

public:  // TODO: protected 로 바꾸기
	Compare comp;
	value_compare(Compare c) : comp(c) {}
	value_compare() : comp(Compare()) {}  // TODO: 반드시 지우기 (테스트 용으로 임시로 만든것임)
};

int main(void)
{
	{
		ft::map<char, int> mp;

		for (int i = 0; i < 26; i++)
		{
			mp.insert(ft::make_pair('a' + i, i));
			std::cout << "size: " << mp.size() << std::endl;
		}
		mp.print();
	}
	system("leaks a.out");

	return (0);
}
