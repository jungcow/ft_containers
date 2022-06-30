#ifndef __VECTOR_GET_ALLOCATOR_H__
#define __VECTOR_GET_ALLOCATOR_H__

#include "../../global/tester_result.hpp"
#include "../../global/tester_util.hpp"
#include "../base/method_base.hpp"
#include "../base/vector_given_base.hpp"

namespace Test
{
	namespace VectorMethod
	{
		class GetAllocator;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class GetAllocatorGiven;
	}
}

template <class Cont>
class Test::VectorUtil::GetAllocatorGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	GetAllocatorGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	Test::TesterResult<typename Cont::allocator_type> when()
	{
		return (Test::TesterUtil<typename Cont::allocator_type>()
					.template impl<Cont>(this->c, &Cont::get_allocator));
	}
};

class Test::VectorMethod::GetAllocator : public Test::MethodBase
{
public:
	template <class Cont>
	Test::VectorUtil::GetAllocatorGiven<Cont> given(Cont& c)
	{
		return (VectorUtil::GetAllocatorGiven<Cont>(c));
	}
};

#endif
