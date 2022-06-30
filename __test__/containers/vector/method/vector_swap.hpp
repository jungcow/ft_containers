#ifndef __VECTOR_SWAP_H__
#define __VECTOR_SWAP_H__

#include "../../global/tester_result.hpp"
#include "../../global/tester_util.hpp"
#include "../base/method_base.hpp"
#include "../base/vector_given_base.hpp"

namespace Test
{
	namespace VectorMethod
	{
		class Swap;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class SwapGiven;
	}
}

template <class Cont>
class Test::VectorUtil::SwapGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	SwapGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	Test::TesterResult<void> when(Cont& x)
	{
		return (Test::TesterUtil<void>()
					.template impl<Cont, Cont&>(this->c, &Cont::swap, x));
	}
};

class Test::VectorMethod::Swap : public Test::MethodBase
{
public:
	template <class Cont>
	Test::VectorUtil::SwapGiven<Cont> given(Cont& c)
	{
		return (VectorUtil::SwapGiven<Cont>(c));
	}
};

#endif
