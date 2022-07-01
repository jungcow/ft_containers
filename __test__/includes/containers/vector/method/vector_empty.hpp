#ifndef __VECTOR_EMPTY_H__
#define __VECTOR_EMPTY_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/tester_util.hpp"

namespace ContainerAssured
{
	namespace VectorMethod
	{
		class Empty;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class EmptyGiven;
	}
}

template <class Cont>
class ContainerAssured::VectorUtil::EmptyGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	EmptyGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	ContainerAssured::TesterResult<bool> when()
	{
		return (ContainerAssured::When<bool>()
					.template impl<Cont>(this->c, &Cont::empty));
	}
};

class ContainerAssured::VectorMethod::Empty : public ContainerAssured::MethodBase
{
public:
	template <class Cont>
	ContainerAssured::VectorUtil::EmptyGiven<Cont> given(Cont& container)
	{
		return (VectorUtil::EmptyGiven<Cont>(container));
	}
};

#endif