#ifndef __VECTOR_ASSIGN_H__
#define __VECTOR_ASSIGN_H__

#include "../../global/tester_result.hpp"
#include "../../global/tester_util.hpp"
#include "../../global/type.hpp"
#include "../base/method_base.hpp"
#include "../base/vector_given_base.hpp"
#include "type.hpp"

namespace Test
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
class Test::VectorUtil::AssignGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	AssignGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	// TODO: exception 관리
	template <class InputIterator>
	Test::TesterResult<void> when(InputIterator first, InputIterator last)
	{
		return (Test::TesterUtil()
					.impl<Cont,
						  InputIterator,
						  InputIterator>(this->c, &Cont::assign, first, last));
	}

	Test::TesterResult<void> when(typename __base::size_type n, typename __base::value_type& val)
	{
		return (Test::TesterUtil()
					.impl<Cont,
						  typename __base::size_type,
						  typename __base::const_reference>(this->c, &Cont::assign, n, val));
	}
};

class Test::VectorMethod::Assign : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::AssignGiven<Cont> given(Cont& c)
	{
		return (VectorUtil::AssignGiven<Cont>(c));
	}
};

#endif
