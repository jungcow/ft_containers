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
		// typedef std::allocator<int>::rebind<ft::tree::Node<int> >::other nodeAlloc;
		// nodeAlloc na;

		// std::cout << typeid(nodeAlloc).name() << std::endl;
		std::cout << std::boolalpha;
		std::cout << (ft::is_pair<std::map<ft::pair<int, int>, ft::pair<char, char> >::value_type>::value) << std::endl;
	}
	{
		ft::map<char, int> mp;

		// mp.insert(ft::make_pair('a', '1'));
		// std::cout << mp.size() << std::endl;
		// mp.insert(ft::make_pair('b', '2'));
		// std::cout << mp.size() << std::endl;

		// for (int i = 0; i < 24; i++)
		// {
		// 	mp.insert(ft::make_pair('a' + i, i));
		// 	std::cout << "size: " << mp.size() << std::endl;
		// }
		// mp.print();

		// int i = 99;
		// while (i++ < 100)
		// {
		// 	ft::map<char, int> mymap;

		// 	ft::tree::BSTree<ft::pair<char, int>, ft::map<char, int>::value_compare> bst(mymap.value_comp());

		// 	bst.insert(ft::make_pair('c', 3));
		// 	bst.printByInOrderTraversal();
		// 	bst.insert(ft::make_pair('e', 3));
		// 	bst.printByInOrderTraversal();
		// 	bst.insert(ft::make_pair('d', 3));
		// 	bst.printByInOrderTraversal();
		// 	bst.insert(ft::make_pair('f', 3));
		// 	std::cout << bst.size() << std::endl;
		// 	bst.printByInOrderTraversal();
		// 	std::cout << bst.find(ft::make_pair('d', 3))->getValue().first << std::endl;
		// 	std::cout << bst.erase(ft::make_pair('e', 3)) << std::endl;
		// 	std::cout << bst.size() << std::endl;
		// 	bst.printByInOrderTraversal();
		// 	std::cout << bst.erase(ft::make_pair('d', 3)) << std::endl;
		// 	bst.printByInOrderTraversal();
		// 	std::cout << bst.size() << std::endl;
		// }
	}
	system("leaks a.out");

	return (0);
}
