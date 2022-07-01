#ifndef __VECTOR_RESERVE_H__
#define __VECTOR_RESERVE_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/when.hpp"

namespace ContainerAssured
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
class ContainerAssured::VectorUtil::ReserveGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	ReserveGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	ContainerAssured::TesterResult<Cont, void, typename oneParameterPack<typename __base::size_type>::type>
	when(typename __base::size_type n)
	{
		return (ContainerAssured::When<void>()
					.template impl<Cont,
								   typename __base::size_type>(this->c, &Cont::reserve, n));
	}
};

class ContainerAssured::VectorMethod::Reserve : public ContainerAssured::MethodBase
{
public:
	template <class Cont>
	ContainerAssured::VectorUtil::ReserveGiven<Cont> given(Cont& container)
	{
		return (VectorUtil::ReserveGiven<Cont>(container));
	}
};

#endif
