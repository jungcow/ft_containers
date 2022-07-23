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
		mp.erase('c');
		mp.print();
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
		mp.print();
		mp.erase('c');
		mp.print();
		mp.erase('t');
		mp.print();
		mp.erase('w');
		mp.print();
		mp.erase('q');
		mp.print();
		mp.erase('e');
		mp.print();
		mp.erase('h');
		mp.print();
		mp.erase('a');
		mp.print();
		mp.erase('b');
		mp.print();
		mp.erase('x');
		mp.print();
		mp.erase('v');
		mp.print();
		mp.erase('f');
		mp.print();
		mp.erase('i');
		mp.print();
		mp.erase('l');
		mp.print();
		mp.erase('u');
		mp.print();
		mp.erase('d');
		mp.print();
		mp.erase('g');
		mp.print();
		mp.erase('j');
		mp.print();
		mp.erase('l');  // duplicated
		mp.print();
		mp.erase('m');
		mp.print();
		mp.erase('n');
		mp.print();
		mp.erase('o');
		mp.print();
		mp.erase('p');
		mp.print();
		mp.erase('s');
		mp.print();
		mp.erase('k');
	}
	{
		ft::map<char, int> mp;

		for (int i = 0; i < 24; i++)
		{
			mp.insert(ft::make_pair('a' + i, i));
			std::cout << "size: " << mp.size() << std::endl;
		}

		std::cout << (*mp.begin()).first << std::endl;
		std::cout << (*mp.end()).first << std::endl;
		std::cout << "find: " << mp.count('k') << std::endl;
		std::cout << "find: " << mp.count('z') << std::endl;
		std::cout << "maxsize: " << mp.max_size() << std::endl;
		mp['z'] = 26;
		mp['a'] = 26;
		std::cout << "z: " <<  mp['z'] << std::endl;
		std::cout << "a: " << mp['a'] << std::endl;
		ft::map<char, int>::iterator mpi = mp.begin();
		mp.print();
		// ++mpi;
		std::cout << "*a++: " <<  (*(mpi++)).first << std::endl;
		std::cout << "*a++: " << (*(mpi++)).first << std::endl;
		std::cout << "*a++: " << (*(mpi++)).first << std::endl;
		std::cout << "*a++: " << (*(mpi++)).first << std::endl;
		std::cout << "*a++: " << (*(mpi++)).first << std::endl;
	}
	{
		// std::map<char, int> mp;
		// for (int i = 0; i < 24; i++)
		// {
		// 	mp.insert(std::make_pair('a' + i, i));
		// }
		// std::map<char, int>::iterator mpi = mp.insert(mp.begin(), std::pair<char, int>('z', 26));

		// std::cout << (*mpi).first << std::endl;
		// std::cout << (*mp.begin()).first << std::endl;

		// for (std::map<char, int>::iterator it = mp.begin(); it != mp.end(); it++)
		// {
		// 	std::cout << (*it).first << std::endl;
		// }
	}
	// system("leaks a.out");

	return (0);
}
