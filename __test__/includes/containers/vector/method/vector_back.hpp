#ifndef __VECTOR_BACK_H__
#define __VECTOR_BACK_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/when.hpp"

namespace ContainerAssured
{
	namespace VectorMethod
	{
		class Back;
		class BackConst;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class BackGiven;
		template <class Cont>
		class BackConstGiven;
	}
}

template <class Cont>
class ContainerAssured::VectorUtil::BackGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;
	const char* methodname = "back";

public:
	BackGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	// TODO: UB 관리
	ContainerAssured::TesterResult<Cont, typename __base::reference, voidParameterPack>
	when()
	{
		return (ContainerAssured::When<typename __base::reference>(methodname)
					.template impl<Cont>(this->c, &Cont::back));
	}
};

template <class Cont>
class ContainerAssured::VectorUtil::BackConstGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;
	const char* methodname = "back const";

public:
	BackConstGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	// TODO: UB 관리
	ContainerAssured::TesterResult<Cont, typename __base::const_reference, voidParameterPack>
	when()
	{
		return (ContainerAssured::When<typename __base::const_reference>(methodname)
					.template impl<Cont>(this->c, &Cont::back));
	}
};

class ContainerAssured::VectorMethod::Back : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::BackGiven<Cont> given(Cont& container)
	{
		return VectorUtil::BackGiven<Cont>(container);
	}
};
class ContainerAssured::VectorMethod::BackConst : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::BackConstGiven<Cont> given(Cont& container)
	{
		return VectorUtil::BackConstGiven<Cont>(container);
	}
};

#endif
