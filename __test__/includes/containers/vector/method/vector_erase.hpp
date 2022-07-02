#ifndef __VECTOR_METHOD_H__
#define __VECTOR_METHOD_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/when.hpp"

namespace ContainerAssured
{
	namespace VectorMethod
	{
		class Erase;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class EraseGiven;
	}
}

template <class Cont>
class ContainerAssured::VectorUtil::EraseGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	EraseGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	// TODO: UB 관리
	ContainerAssured::TesterResult<Cont,
								   typename __base::iterator,
								   typename OneParameterPack<typename __base::const_iterator>::type>
	when(typename __base::iterator position)
	{
		return (ContainerAssured::When<typename __base::iterator>()
					.template impl<Cont,
								   typename __base::const_iterator>(this->c, &Cont::erase, position));
	}

	// TODO: UB 관리
	ContainerAssured::TesterResult<Cont, typename __base::iterator,
								   typename TwoParameterPack<typename __base::const_iterator,
															 typename __base::const_iterator>::type>
	when(typename __base::iterator first, typename __base::iterator last)
	{
		return (ContainerAssured::When<typename __base::iterator>()
					.template impl<Cont,
								   typename __base::const_iterator,
								   typename __base::const_iterator>(this->c, &Cont::erase, first, last));
	}
};

class ContainerAssured::VectorMethod::Erase : public ContainerAssured::MethodBase
{
public:
	template <class Cont>
	ContainerAssured::VectorUtil::EraseGiven<Cont> given(Cont& container)
	{
		return (VectorUtil::EraseGiven<Cont>(container));
	}
};

#endif
