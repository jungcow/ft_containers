#ifndef __VECTOR_POP_BACK_H__
#define __VECTOR_POP_BACK_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/tester_util.hpp"

namespace ContainerAssured
{
	namespace VectorMethod
	{
		class PopBack;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class PopBackGiven;
	}
}

template <class Cont>
class ContainerAssured::VectorUtil::PopBackGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	PopBackGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	ContainerAssured::TesterResult<Cont,
								   void,
								   ParameterPack<void, void, void, void> >
	when()
	{
		return (ContainerAssured::When<void>()
					.template impl<Cont>(this->c, &Cont::pop_back));
	}
};

class ContainerAssured::VectorMethod::PopBack : public ContainerAssured::MethodBase
{
public:
	template <class Cont>
	ContainerAssured::VectorUtil::PopBackGiven<Cont> given(Cont& container)
	{
		return (VectorUtil::PopBackGiven<Cont>(container));
	}
};

#endif
