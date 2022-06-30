#ifndef __VECTOR_OPERATOR_ASSIGN_H__
#define __VECTOR_OPERATOR_ASSIGN_H__

#include "../../global/tester_result.hpp"
#include "../../global/tester_util.hpp"
#include "../base/method_base.hpp"
#include "../base/vector_given_base.hpp"

namespace Test
{
	namespace VectorMethod
	{
		class OperatorAssign;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class OperatorAssignGiven;
	}
}

template <class Cont>
class Test::VectorUtil::OperatorAssignGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	OperatorAssignGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	Test::TesterResult<Cont&> when(const Cont& x)
	{
		return (Test::TesterUtil<Cont&>()
					.template impl<Cont,
								   const Cont&>(this->c, &Cont::operator=, x));
	}
};

class Test::VectorMethod::OperatorAssign : public Test::MethodBase
{
public:
	template <class Cont>
	Test::VectorUtil::OperatorAssignGiven<Cont> given(Cont& c)
	{
		return (VectorUtil::OperatorAssignGiven<Cont>(c));
	}
};

#endif
