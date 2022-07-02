#ifndef __VECTOR_ASSIGN_H__
#define __VECTOR_ASSIGN_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/when.hpp"

namespace ContainerAssured
{
	namespace VectorMethod
	{
		class Assign;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class AssignGiven;
	}
}

template <class Cont>
class ContainerAssured::VectorUtil::AssignGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	AssignGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	ContainerAssured::TesterResult<Cont, void,
								   typename TwoParameterPack<typename __base::size_type, typename __base::const_reference>::type>
	when(typename __base::size_type n, const typename __base::value_type& val)
	{
		return (ContainerAssured::When<void>()
					.impl<Cont,
						  typename __base::size_type,
						  typename __base::const_reference>(this->c, &Cont::assign, n, val));
	}

	// TODO: exception 관리
	template <class InputIterator>
	ContainerAssured::TesterResult<Cont, void, typename TwoParameterPack<InputIterator, InputIterator>::type>
	when(typename std::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
	{
		return (ContainerAssured::When<void>()
					.impl<Cont,
						  InputIterator,
						  InputIterator>(this->c, &Cont::assign, first, last));
	}
};

class ContainerAssured::VectorMethod::Assign : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::AssignGiven<Cont> given(Cont& container)
	{
		return (VectorUtil::AssignGiven<Cont>(container));
	}
};

#endif
