#ifndef __VECTOR_EMPTY_H__
#define __VECTOR_EMPTY_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/when.hpp"

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
	const char* methodname = "empty";

public:
	EmptyGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	ContainerAssured::TesterResult<Cont, bool, voidParameterPack>
	when()
	{
		return (ContainerAssured::When<bool>(methodname)
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