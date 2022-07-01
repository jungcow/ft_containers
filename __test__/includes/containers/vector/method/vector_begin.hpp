#ifndef __VECTOR_BEGIN_H__
#define __VECTOR_BEGIN_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/tester_util.hpp"

namespace ContainerAssured
{
	namespace VectorMethod
	{
		class Begin;
		class BeginConst;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class BeginGiven;
		template <class Cont>
		class BeginConstGiven;
	}
}

template <class Cont>
class ContainerAssured::VectorUtil::BeginGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	BeginGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	// TODO: UB 관리
	ContainerAssured::TesterResult<Cont, typename __base::iterator, voidParameterPack>
	when()
	{
		return (ContainerAssured::When<typename __base::iterator>()
					.template impl<Cont>(this->c, &Cont::begin));
	}
};

template <class Cont>
class ContainerAssured::VectorUtil::BeginConstGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	BeginConstGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	// TODO: UB 관리
	ContainerAssured::TesterResult<Cont, typename __base::const_iterator, voidParameterPack>
	when()
	{
		return (ContainerAssured::When<typename __base::const_iterator>()
					.template impl<Cont>(this->c, &Cont::begin));
	}
};

class ContainerAssured::VectorMethod::Begin : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::BeginGiven<Cont> given(Cont& container)
	{
		return VectorUtil::BeginGiven<Cont>(container);
	}
};
class ContainerAssured::VectorMethod::BeginConst : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::BeginConstGiven<Cont> given(Cont& container)
	{
		return VectorUtil::BeginConstGiven<Cont>(container);
	}
};

#endif
