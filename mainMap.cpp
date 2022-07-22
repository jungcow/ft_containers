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

int main(void)
{
	{
		ft::map<char, int> mp;

		for (int i = 0; i < 24; i++)
		{
			mp.insert(ft::make_pair('a' + i, i));
			std::cout << "size: " << mp.size() << std::endl;
		}
		mp.print();

		mp.erase('h');
		mp.erase('t');
		mp.print();
		mp.erase('w');
		mp.print();
		mp.erase('e');
		mp.print();
		mp.erase('r');
		mp.print();
		mp.erase('a');
		mp.print();
		mp.erase('q');
		mp.print();
		mp.erase('c');
		std::cout << mp.size() << std::endl;
	}
	{
		ft::map<char, int> mp;

		for (int i = 0; i < 24; i++)
		{
			mp.insert(ft::make_pair('a' + i, i));
			std::cout << "size: " << mp.size() << std::endl;
		}
		mp.print();

		mp.erase('r');
		mp.erase('c');
		mp.erase('t');
		mp.erase('w');
		mp.erase('q');
		mp.erase('e');
		mp.erase('h');
		mp.erase('a');
		// mp.print();
		// mp.print();
		// mp.print();
		// mp.print();
		mp.print();
	}
	system("leaks a.out");

	return (0);
}
