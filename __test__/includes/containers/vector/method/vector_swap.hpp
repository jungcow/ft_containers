#ifndef __VECTOR_SWAP_H__
#define __VECTOR_SWAP_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/tester_util.hpp"

namespace ContainerAssured
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
class ContainerAssured::VectorUtil::SwapGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	SwapGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	ContainerAssured::TesterResult<Cont, void, 
	ParameterPack<Cont&, void, void, void> > 
	when(Cont& x)
	{
		return (ContainerAssured::When<void>()
					.template impl<Cont, Cont&>(this->c, &Cont::swap, x));
	}
};

class ContainerAssured::VectorMethod::Swap : public ContainerAssured::MethodBase
{
public:
	template <class Cont>
	ContainerAssured::VectorUtil::SwapGiven<Cont> given(Cont& container)
	{
		return (VectorUtil::SwapGiven<Cont>(container));
	}
};

#endif
