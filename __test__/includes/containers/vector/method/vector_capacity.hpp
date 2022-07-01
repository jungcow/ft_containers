#ifndef __VECTOR_CAPACITY_H__
#define __VECTOR_CAPACITY_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/tester_util.hpp"

namespace Test
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
class Test::VectorUtil::CapacityGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	CapacityGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	Test::TesterResult<typename __base::size_type> when()
	{
		return (Test::TesterUtil<typename __base::size_type>()
					.template impl<Cont>(this->c, &Cont::capacity));
	}
};

class Test::VectorMethod::Capacity : public Test::MethodBase
{
public:
	template <class Cont>
	Test::VectorUtil::CapacityGiven<Cont> given(Cont& container)
	{
		return (VectorUtil::CapacityGiven<Cont>(container));
	}
};

#endif
