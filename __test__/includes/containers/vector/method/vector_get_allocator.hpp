#ifndef __VECTOR_GET_ALLOCATOR_H__
#define __VECTOR_GET_ALLOCATOR_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/tester_util.hpp"

namespace ContainerAssured
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
class ContainerAssured::VectorUtil::GetAllocatorGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	GetAllocatorGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	ContainerAssured::TesterResult<typename Cont::allocator_type> when()
	{
		return (ContainerAssured::When<typename Cont::allocator_type>()
					.template impl<Cont>(this->c, &Cont::get_allocator));
	}
};

class ContainerAssured::VectorMethod::GetAllocator : public ContainerAssured::MethodBase
{
public:
	template <class Cont>
	ContainerAssured::VectorUtil::GetAllocatorGiven<Cont> given(Cont& container)
	{
		return (VectorUtil::GetAllocatorGiven<Cont>(container));
	}
};

#endif
