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

	const std::vector<double> constvec(3, 3);
	size_t i = 0;
	std::cout << vtester->at_const()
					 .given(constvec)
					 .when(i)
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << "\n[ Back Tester ]" << std::endl;
	std::cout << vtester->back()
					 .given(vec)
					 .when()
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << vtester->back_const()
					 .given(constvec)
					 .when()
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << "\n[ Begin Tester ]" << std::endl;
	std::cout << vtester->begin()
					 .given(vec)
					 .when()
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << vtester->begin_const()
					 .given(constvec)
					 .when()
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << "\n[ Capacity Tester ]" << std::endl;
	std::cout << vtester->capacity()
					 .given(vec)
					 .when()
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << vtester->capacity()
					 .given(constvec)
					 .when()
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << "\n[ Clear Tester ]" << std::endl;
	std::cout << vtester->clear()
					 .given(vec)
					 .when()
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << "\n[ Empty Tester ]" << std::endl;
	std::cout << vtester->empty()
					 .given(vec)
					 .when()
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << vtester->empty()
					 .given(constvec)
					 .when()
					 .info<NANOSECONDS>()
			  << std::endl;

	std::vector<double> vec2(10, 9);
	const std::vector<double> constvec2(10, 5.5);
	std::cout << "\n[ End Tester ]" << std::endl;
	std::cout << vtester->end()
					 .given(vec2)
					 .when()
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << vtester->end_const()
					 .given(constvec2)
					 .when()
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << "\n[ Front Tester ]" << std::endl;
	std::cout << vtester->front()
					 .given(vec2)
					 .when()
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << vtester->front_const()
					 .given(constvec2)
					 .when()
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << "\n[ Get_Allocator Tester ]" << std::endl;
	std::cout << vtester->get_allocator()
					 .given(vec2)
					 .when()
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << vtester->get_allocator()
					 .given(constvec2)
					 .when()
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << "\n[ Insert Tester ]" << std::endl;
	std::cout << vtester->insert()
					 .given(vec2)
					 .when(vec2.begin() + 2, 4)
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << vtester->insert()
					 .given(vec2)
					 .when(vec2.begin() + 2, 5, 11.2)
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << vtester->insert()
					 .given(vec2)
					 .when(vec2.begin() + 3, vec2.end() - 3, vec2.end())
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << "\n[ Assignment Operator Tester ]" << std::endl;
	std::vector<double> vec3(7, 20);
	std::cout << vtester->operator_assign()
					 .given(vec2)
					 .when(vec3)
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << "\n[ Array Index Operator Tester ]" << std::endl;
	std::cout << vtester->operator_index()
					 .given(vec2)
					 .when(3)
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << vtester->operator_index_const()
					 .given(constvec2)
					 .when(3)
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << "\n[ Pop Back Tester ]" << std::endl;
	std::cout << vtester->pop_back()
					 .given(vec3)
					 .when()
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << "\n[ Push Back Tester ]" << std::endl;
	std::cout << vtester->push_back()
					 .given(vec3)
					 .when(222)
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << "\n[ rbegin Tester ]" << std::endl;
	std::cout << vtester->rbegin()
					 .given(vec3)
					 .when()
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << vtester->rbegin_const()
					 .given(constvec2)
					 .when()
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << "\n[ rend Tester ]" << std::endl;
	std::cout << vtester->rend()
					 .given(vec3)
					 .when()
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << vtester->rend_const()
					 .given(constvec2)
					 .when()
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << "\n[ Reserve Tester ]" << std::endl;
	std::cout << vtester->reserve()
					 .given(vec3)
					 .when(222)
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << "\n[ Resize Tester ]" << std::endl;
	std::cout << vtester->resize()
					 .given(vec3)
					 .when(188)
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << vtester->resize()
					 .given(vec3)
					 .when(200, 88)
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << "\n[ Size Tester ]" << std::endl;
	std::cout << vtester->size()
					 .given(vec3)
					 .when()
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << vtester->size()
					 .given(constvec2)
					 .when()
					 .info<NANOSECONDS>()
			  << std::endl;
	std::cout << "\n[ Swap Tester ]" << std::endl;
	std::vector<double> vec4(101, 101);
	std::cout << vtester->swap()
					 .given(vec3)
					 .when(vec4)
					 .info<NANOSECONDS>()
			  << std::endl;
}
