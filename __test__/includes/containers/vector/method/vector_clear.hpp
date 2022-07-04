#ifndef __VECTOR_CLEAR_H__
#define __VECTOR_CLEAR_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/when.hpp"

namespace ContainerAssured
{
	namespace VectorMethod
	{
		class Clear;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class ClearGiven;
	}
}

template <class Cont>
class ContainerAssured::VectorUtil::ClearGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;
	const char* methodname = "clear";

public:
	ClearGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	ContainerAssured::TesterResult<Cont, void, voidParameterPack>
	when()
	{
		return (ContainerAssured::When<void>(methodname)
					.template impl<Cont>(this->c, &Cont::clear));
	}
};

class ContainerAssured::VectorMethod::Clear : public ContainerAssured::MethodBase
{
public:
	template <class Cont>
	ContainerAssured::VectorUtil::ClearGiven<Cont> given(Cont& container)
	{
		return (VectorUtil::ClearGiven<Cont>(container));
	}
};

#endif
