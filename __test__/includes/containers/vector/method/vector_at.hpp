#ifndef __VECTOR_AT_H__
#define __VECTOR_AT_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/when.hpp"

namespace ContainerAssured
{
	namespace VectorMethod
	{
		class At;
		class AtConst;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class AtGiven;
		template <class Cont>
		class AtConstGiven;
	}
}

template <class Cont>
class ContainerAssured::VectorUtil::AtGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	AtGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	// TODO: exception 관리
	ContainerAssured::TesterResult<Cont,
								   typename __base::reference,
								   typename OneParameterPack<typename __base::size_type>::type>
	when(typename __base::size_type n)
	{
		return (ContainerAssured::When<typename __base::reference>()
					.template impl<Cont,
								   typename __base::size_type>(this->c, &Cont::at, n));
	}
};
template <class Cont>
class ContainerAssured::VectorUtil::AtConstGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	AtConstGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	// TODO: exception 관리
	ContainerAssured::TesterResult<Cont,
								   typename __base::const_reference,
								   typename OneParameterPack<typename __base::size_type>::type>
	when(typename __base::size_type n)
	{
		return (ContainerAssured::When<typename __base::const_reference>()
					.template impl<Cont,
								   typename __base::size_type>(this->c, &Cont::at, n));
	}
};

class ContainerAssured::VectorMethod::At : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::AtGiven<Cont> given(Cont& container)
	{
		return VectorUtil::AtGiven<Cont>(container);
	}
};
class ContainerAssured::VectorMethod::AtConst : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::AtConstGiven<Cont> given(Cont& container)
	{
		return VectorUtil::AtConstGiven<Cont>(container);
	}
};

#endif
