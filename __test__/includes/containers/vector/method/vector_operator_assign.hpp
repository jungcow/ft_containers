#ifndef __VECTOR_OPERATOR_ASSIGN_H__
#define __VECTOR_OPERATOR_ASSIGN_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/tester_util.hpp"

namespace ContainerAssured
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
class ContainerAssured::VectorUtil::OperatorAssignGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	OperatorAssignGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	ContainerAssured::TesterResult<Cont&> when(const Cont& x)
	{
		return (ContainerAssured::When<Cont&>()
					.template impl<Cont,
								   const Cont&>(this->c, &Cont::operator=, x));
	}
};

class ContainerAssured::VectorMethod::OperatorAssign : public ContainerAssured::MethodBase
{
public:
	template <class Cont>
	ContainerAssured::VectorUtil::OperatorAssignGiven<Cont> given(Cont& container)
	{
		return (VectorUtil::OperatorAssignGiven<Cont>(container));
	}
};

#endif
