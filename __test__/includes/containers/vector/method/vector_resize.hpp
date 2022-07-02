#ifndef __VECTOR_RESIZE_H__
#define __VECTOR_RESIZE_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/when.hpp"

namespace ContainerAssured
{
	namespace VectorMethod
	{
		class Resize;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class ResizeGiven;
	}
}

template <class Cont>
class ContainerAssured::VectorUtil::ResizeGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	ResizeGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	ContainerAssured::TesterResult<Cont, void,
								   typename TwoParameterPack<typename __base::size_type,
															 typename __base::const_reference>::type>
	when(typename __base::size_type n,
		 typename __base::value_type val = typename __base::value_type())
	{
		return (ContainerAssured::When<void>()
					.template impl<Cont,
								   typename __base::size_type,
								   typename __base::const_reference>(this->c, &Cont::resize, n, val));
	}
};

class ContainerAssured::VectorMethod::Resize : public ContainerAssured::MethodBase
{
public:
	template <class Cont>
	ContainerAssured::VectorUtil::ResizeGiven<Cont> given(Cont& container)
	{
		return (VectorUtil::ResizeGiven<Cont>(container));
	}
};

#endif
