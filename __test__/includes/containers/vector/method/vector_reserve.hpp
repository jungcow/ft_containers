#ifndef __VECTOR_RESERVE_H__
#define __VECTOR_RESERVE_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/tester_util.hpp"

namespace Test
{
	namespace VectorMethod
	{
		class Reserve;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class ReserveGiven;
	}
}

template <class Cont>
class Test::VectorUtil::ReserveGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	ReserveGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	Test::TesterResult<void> when(typename __base::size_type n)
	{
		return (Test::TesterUtil<void>()
					.template impl<Cont,
								   typename __base::size_type>(this->c, &Cont::reserve, n));
	}
};

class Test::VectorMethod::Reserve : public Test::MethodBase
{
public:
	template <class Cont>
	Test::VectorUtil::ReserveGiven<Cont> given(Cont& container)
	{
		return (VectorUtil::ReserveGiven<Cont>(container));
	}
};

#endif
