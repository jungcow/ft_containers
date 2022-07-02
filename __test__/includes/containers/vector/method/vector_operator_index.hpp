#ifndef __VECTOR_OPERATOR_INDEX_H__
#define __VECTOR_OPERATOR_INDEX_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/when.hpp"

namespace ContainerAssured
{
	namespace VectorMethod
	{
		class OperatorIndex;
		class OperatorIndexConst;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class OperatorIndexGiven;
		template <class Cont>
		class OperatorIndexConstGiven;
	}
}

template <class Cont>
class ContainerAssured::VectorUtil::OperatorIndexGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	OperatorIndexGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	// TODO: UB 관리
	ContainerAssured::TesterResult<Cont,
								   typename __base::reference,
								   typename OneParameterPack<typename __base::size_type>::type>
	when(typename __base::size_type n)
	{
		return (ContainerAssured::When<typename __base::reference>()
					.template impl<Cont, typename __base::size_type>(this->c, &Cont::operator[], n));
	}
};

template <class Cont>
class ContainerAssured::VectorUtil::OperatorIndexConstGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	OperatorIndexConstGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	// TODO: UB 관리
	ContainerAssured::TesterResult<Cont,
								   typename __base::const_reference,
								   typename OneParameterPack<typename __base::size_type>::type>
	when(typename __base::size_type n)
	{
		return (ContainerAssured::When<typename __base::const_reference>()
					.template impl<Cont, typename __base::size_type>(this->c, &Cont::operator[], n));
	}
};

class ContainerAssured::VectorMethod::OperatorIndex : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::OperatorIndexGiven<Cont> given(Cont& container)
	{
		return VectorUtil::OperatorIndexGiven<Cont>(container);
	}
};
class ContainerAssured::VectorMethod::OperatorIndexConst : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::OperatorIndexConstGiven<Cont> given(Cont& container)
	{
		return VectorUtil::OperatorIndexConstGiven<Cont>(container);
	}
};

#endif
