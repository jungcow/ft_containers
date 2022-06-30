#ifndef __VECTOR_TESTER_H__
#define __VECTOR_TESTER_H__

#include <iostream>

#include "./vector_method.hpp"

namespace Test
{
	class VectorTester
	{
	public:
		VectorTester()
		{
			// std::cout << "VectorTester default constructor" << '\n';
		}

		VectorMethod::Erase erase()
		{
			return (VectorMethod::Erase());
		}
	};
}

#endif
