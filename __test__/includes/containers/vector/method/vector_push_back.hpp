#ifndef __VECTOR_PUSH_BACK_H__
#define __VECTOR_PUSH_BACK_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/when.hpp"

namespace ContainerAssured
{
	namespace VectorMethod
	{
		class PushBack;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class PushBackGiven;
	}
}

template <class Cont>
class ContainerAssured::VectorUtil::PushBackGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	PushBackGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	ContainerAssured::TesterResult<Cont, void, typename oneParameterPack<typename __base::const_reference>::type>
	when(typename __base::const_reference val)
	{
		return (ContainerAssured::When<void>()
					.template impl<Cont,
								   typename __base::const_reference>(this->c, &Cont::push_back, val));
	}
};

class ContainerAssured::VectorMethod::PushBack : public ContainerAssured::MethodBase
{
public:
	template <class Cont>
	ContainerAssured::VectorUtil::PushBackGiven<Cont> given(Cont& container)
	{
		return (VectorUtil::PushBackGiven<Cont>(container));
	}
};

#endif
