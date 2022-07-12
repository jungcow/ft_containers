#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>

#include "map.hpp"
#include "tree.hpp"
#include "type.hpp"
#include "utility.hpp"

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
		int i = 99;
		while (i++ < 100)
		{
			ft::map<char, int> mymap;

			ft::tree::BSTree<ft::pair<char, int>, ft::map<char, int>::value_compare> bst(mymap.value_comp());

			bst.insert(ft::make_pair('c', 3));
			bst.printByInOrderTraversal();
			bst.insert(ft::make_pair('e', 3));
			bst.printByInOrderTraversal();
			bst.insert(ft::make_pair('d', 3));
			bst.printByInOrderTraversal();
			bst.insert(ft::make_pair('f', 3));
			std::cout << bst.size() << std::endl;
			bst.printByInOrderTraversal();
			std::cout << bst.find(ft::make_pair('d', 3))->getValue().first << std::endl;
			std::cout << bst.erase(ft::make_pair('e', 3)) << std::endl;
			std::cout << bst.size() << std::endl;
			bst.printByInOrderTraversal();
			std::cout << bst.erase(ft::make_pair('d', 3)) << std::endl;
			bst.printByInOrderTraversal();
			std::cout << bst.size() << std::endl;
		}
		system("leaks a.out");
	}

	return (0);
}
