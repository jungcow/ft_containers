#ifndef __VECTOR_TESTER_H__
#define __VECTOR_TESTER_H__

#include <iostream>

#include "./method/vector_assign.hpp"
#include "./method/vector_at.hpp"
#include "./method/vector_back.hpp"
#include "./method/vector_begin.hpp"
#include "./method/vector_capacity.hpp"
#include "./method/vector_clear.hpp"
#include "./method/vector_empty.hpp"
#include "./method/vector_end.hpp"
#include "./method/vector_erase.hpp"
#include "./method/vector_front.hpp"
#include "./method/vector_get_allocator.hpp"
#include "./method/vector_insert.hpp"
#include "./method/vector_max_size.hpp"
#include "./method/vector_operator_assign.hpp"
#include "./method/vector_operator_index.hpp"
#include "./method/vector_pop_back.hpp"
#include "./method/vector_push_back.hpp"
#include "./method/vector_rbegin.hpp"
#include "./method/vector_rend.hpp"
#include "./method/vector_reserve.hpp"
#include "./method/vector_resize.hpp"
#include "./method/vector_size.hpp"
#include "./method/vector_swap.hpp"
#if 0
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
		VectorMethod::Back back() { return (VectorMethod::Back()); }
		VectorMethod::BackConst back_const() { return (VectorMethod::BackConst()); }
		VectorMethod::Begin begin() { return (VectorMethod::Begin()); }
		VectorMethod::BeginConst begin_const() { return (VectorMethod::BeginConst()); }
		VectorMethod::Capacity capacity() { return (VectorMethod::Capacity()); }
		VectorMethod::Clear clear() { return (VectorMethod::Clear()); }
		VectorMethod::Empty empty() { return (VectorMethod::Empty()); }
		VectorMethod::End end() { return (VectorMethod::End()); }
		VectorMethod::EndConst end_const() { return (VectorMethod::EndConst()); }
		VectorMethod::Front front() { return (VectorMethod::Front()); }
		VectorMethod::FrontConst front_const() { return (VectorMethod::FrontConst()); }
		VectorMethod::GetAllocator get_allocator() { return (VectorMethod::GetAllocator()); }
		VectorMethod::Insert insert() { return (VectorMethod::Insert()); }
		VectorMethod::MaxSize max_size() { return (VectorMethod::MaxSize()); }
		VectorMethod::OperatorAssign operator_assign() { return (VectorMethod::OperatorAssign()); }
		VectorMethod::OperatorIndex operator_index() { return (VectorMethod::OperatorIndex()); }
		VectorMethod::OperatorIndexConst operator_index_const() { return (VectorMethod::OperatorIndexConst()); }
		VectorMethod::PopBack pop_back() { return (VectorMethod::PopBack()); }
		VectorMethod::PushBack push_back() { return (VectorMethod::PushBack()); }
		VectorMethod::RBegin rbegin() { return (VectorMethod::RBegin()); }
		VectorMethod::RBeginConst rbegin_const() { return (VectorMethod::RBeginConst()); }
		VectorMethod::REnd rend() { return (VectorMethod::REnd()); }
		VectorMethod::REndConst rend_const() { return (VectorMethod::REndConst()); }
		VectorMethod::Reserve reserve() { return (VectorMethod::Reserve()); }
		VectorMethod::Resize resize() { return (VectorMethod::Resize()); }
		VectorMethod::Size size() { return (VectorMethod::Size()); }
		VectorMethod::Swap swap() { return (VectorMethod::Swap()); }
	};
}

#endif
