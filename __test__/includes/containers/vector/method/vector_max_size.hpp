#ifndef __VECTOR_MAX_SIZE_H__
#define __VECTOR_MAX_SIZE_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/tester_util.hpp"

namespace ContainerAssured
{
	namespace VectorMethod
	{
		class MaxSize;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class MaxSizeGiven;
	}
}

template <class Cont>
class ContainerAssured::VectorUtil::MaxSizeGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	MaxSizeGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	ContainerAssured::TesterResult<Cont,
								   typename __base::size_type,
								   voidParameterPack>
	when()
	{
		return (ContainerAssured::When<typename __base::size_type>()
					.template impl<Cont>(this->c, &Cont::max_size));
	}
};

class ContainerAssured::VectorMethod::MaxSize : public ContainerAssured::MethodBase
{
public:
	template <class Cont>
	ContainerAssured::VectorUtil::MaxSizeGiven<Cont> given(Cont& container)
	{
		return (VectorUtil::MaxSizeGiven<Cont>(container));
	}
};

#endif
