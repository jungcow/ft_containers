#ifndef __VECTOR_ASSIGN_H__
#define __VECTOR_ASSIGN_H__

#include "../../global/tester_result.hpp"
#include "../../global/tester_util.hpp"
#include "../../global/type.hpp"
#include "../base/given_base.hpp"
#include "../base/method_base.hpp"
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
class VectorUtil::AssignGiven : public Test::Base::GivenBase<Cont>
{
private:
	typedef typename Cont::size_type size_type;
	typedef typename Cont::value_type value_type;
	typedef typename Cont::const_reference const_reference;

public:
	AssignGiven(Cont& input) : Test::Base::GivenBase<Cont>(input) {}

	// TODO: exception 관리
	template <class InputIterator>
	Test::TesterResult<void> when(InputIterator first, InputIterator last)
	{
		return (Test::TesterUtil()
					.impl<Cont,
						  InputIterator,
						  InputIterator>(this->c, &Cont::assign, first, last));
	}

	Test::TesterResult<void> when(size_type n, value_type& val)
	{
		// std::cout << "const_reference: " << type(const_reference()) << std::endl;
		// std::cout << "value_type&: " << type(val) << std::endl;
		return (Test::TesterUtil()
					.impl<Cont,
						  size_type,
						  const_reference>(this->c, &Cont::assign, n, val));
	}
};

class VectorMethod::Assign : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::AssignGiven<Cont> given(Cont& c)
	{
		return (VectorUtil::AssignGiven<Cont>(c));
	}
};

#endif
