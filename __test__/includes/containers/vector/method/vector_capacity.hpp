#ifndef __VECTOR_CAPACITY_H__
#define __VECTOR_CAPACITY_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/tester_util.hpp"

namespace ContainerAssured
{
	namespace VectorMethod
	{
		class Capacity;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class CapacityGiven;
	}
}

template <class Cont>
class ContainerAssured::VectorUtil::CapacityGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	CapacityGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	ContainerAssured::TesterResult<typename __base::size_type> when()
	{
		return (ContainerAssured::When<typename __base::size_type>()
					.template impl<Cont>(this->c, &Cont::capacity));
	}
};

class ContainerAssured::VectorMethod::Capacity : public ContainerAssured::MethodBase
{
public:
	template <class Cont>
	ContainerAssured::VectorUtil::CapacityGiven<Cont> given(Cont& container)
	{
		return (VectorUtil::CapacityGiven<Cont>(container));
	}
};

#endif
