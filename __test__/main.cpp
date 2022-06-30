#include <iostream>
#include <vector>

#include "containers/vector/vector_tester.hpp"
#include "global/tester.hpp"
#include "type.hpp"

using namespace Test;

void hello(void)
{
	system("leaks container_tester");
}

int main(void)
{
#if LEAKS
	atexit(hello);
#endif

	std::cout << "\n[ Erase Tester ]" << std::endl;
	Tester<VectorTester> vtester;
	std::vector<double> vec(10, 8);
	std::vector<double>::iterator vi;
	std::vector<double>::iterator from;
	std::vector<double>::iterator to;

	vi = vec.begin() + 1;
	from = vec.begin() + 2;
	to = vec.end() - 3;

	std::cout << vec.size() << std::endl;
	std::cout << vtester->erase()
					 .given(vec)
					 .when(vi)
					 .info<NANOSECONDS>()
			  << std::endl;

	std::cout << vec.size() << std::endl;
	std::cout << vtester->erase()
					 .given(vec)
					 .when(from, to)
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << vec.size() << std::endl;

	std::cout << "\n[ Assign Tester ]" << std::endl;
	size_t ai = 20;
	double ad = 3.3;

	std::cout << vtester->assign()
					 .given(vec)
					 .when(ai, ad)
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "vec[3]: " << vec[3] << std::endl;

	std::vector<double> assign_vec(1000, 8.8);

	std::cout << vtester->assign()
					 .given(vec)
					 .when(assign_vec.begin(), assign_vec.end())
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "vec[3]: " << vec[3] << std::endl;

	std::cout << "\n[ At Tester ]" << std::endl;
	std::cout << vtester->at()
					 .given(vec)
					 .when(3)
					 .info<NANOSECONDS>()
			  << std::endl;
	const std::vector<double> atconstvec(3, 3);
	size_t i = 0;
	std::cout << vtester->at_const()
					 .given(atconstvec)
					 .when(i)
					 .info<NANOSECONDS>()
			  << std::endl;
}
