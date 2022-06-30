#ifndef __VECTOR_TESTER_H__
#define __VECTOR_TESTER_H__

#include <iostream>

#include "./method/vector_assign.hpp"
#include "./method/vector_at.hpp"
#if 0
#include "./method/vector_back.hpp"
#include "./method/vector_begin.hpp"
#include "./method/vector_capacity.hpp"
#include "./method/vector_clear.hpp"
#include "./method/vector_empty.hpp"
#include "./method/vector_end.hpp"
#endif
#include "./method/vector_erase.hpp"
#if 0
#include "./method/vector_front.hpp"
#include "./method/vector_get_allocator.hpp"
#include "./method/vector_insert.hpp"
#include "./method/vector_max_size.hpp"
#include "./method/vector_operator=.hpp"
#include "./method/vector_operator[].hpp"
#include "./method/vector_pop_back.hpp"
#include "./method/vector_push_back.hpp"
#include "./method/vector_rbegin.hpp"
#include "./method/vector_rend.hpp"
#include "./method/vector_reserve.hpp"
#include "./method/vector_resize.hpp"
#include "./method/vector_size.hpp"
#include "./method/vector_swap.hpp"
#endif
namespace Test
{
	class VectorTester
	{
	public:
		VectorTester() {}

		VectorMethod::Erase erase() { return (VectorMethod::Erase()); }
		VectorMethod::Assign assign() { return (VectorMethod::Assign()); }
		VectorMethod::At at() { return (VectorMethod::At()); }
		VectorMethod::AtConst at_const() { return (VectorMethod::AtConst()); }
	};
}

#endif
