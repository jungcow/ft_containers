#ifndef __VECTOR_SIZE_H__
#define __VECTOR_SIZE_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/tester_util.hpp"

namespace ContainerAssured
{
	namespace VectorMethod
	{
		class Size;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class SizeGiven;
	}
}

template <class Cont>
class ContainerAssured::VectorUtil::SizeGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	SizeGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	ContainerAssured::TesterResult<Cont, typename __base::size_type, voidParameterPack>
	when()
	{
		return (ContainerAssured::When<typename __base::size_type>()
					.template impl<Cont>(this->c, &Cont::size));
	}
};

class ContainerAssured::VectorMethod::Size : public ContainerAssured::MethodBase
{
public:
	template <class Cont>
	ContainerAssured::VectorUtil::SizeGiven<Cont> given(Cont& container)
	{
		return (VectorUtil::SizeGiven<Cont>(container));
	}
};

#endif