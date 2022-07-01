#ifndef __VECTOR_FRONT_H__
#define __VECTOR_FRONT_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/tester_util.hpp"

namespace ContainerAssured
{
	namespace VectorMethod
	{
		class Front;
		class FrontConst;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class FrontGiven;
		template <class Cont>
		class FrontConstGiven;
	}
}

template <class Cont>
class ContainerAssured::VectorUtil::FrontGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	FrontGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	// TODO: UB 관리
	ContainerAssured::TesterResult<Cont,
								   typename __base::reference,
								   voidParameterPack>
	when()
	{
		return (ContainerAssured::When<typename __base::reference>()
					.template impl<Cont>(this->c, &Cont::front));
	}
};

template <class Cont>
class ContainerAssured::VectorUtil::FrontConstGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	FrontConstGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	// TODO: UB 관리
	ContainerAssured::TesterResult<Cont,
								   typename __base::const_reference,
								   voidParameterPack>
	when()
	{
		return (ContainerAssured::When<typename __base::const_reference>()
					.template impl<Cont>(this->c, &Cont::front));
	}
};

class ContainerAssured::VectorMethod::Front : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::FrontGiven<Cont> given(Cont& container)
	{
		return VectorUtil::FrontGiven<Cont>(container);
	}
};
class ContainerAssured::VectorMethod::FrontConst : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::FrontConstGiven<Cont> given(Cont& container)
	{
		return VectorUtil::FrontConstGiven<Cont>(container);
	}
};

#endif
