#ifndef __VECTOR_EMPTY_H__
#define __VECTOR_EMPTY_H__

#include "../../global/tester_result.hpp"
#include "../../global/tester_util.hpp"
#include "../base/method_base.hpp"
#include "../base/vector_given_base.hpp"

namespace Test
{
	namespace VectorMethod
	{
		class Empty;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class EmptyGiven;
	}
}

template <class Cont>
class Test::VectorUtil::EmptyGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	EmptyGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	Test::TesterResult<bool> when()
	{
		return (Test::TesterUtil<bool>()
					.template impl<Cont>(this->c, &Cont::empty));
	}
};

class Test::VectorMethod::Empty : public Test::MethodBase
{
public:
	template <class Cont>
	Test::VectorUtil::EmptyGiven<Cont> given(Cont& c)
	{
		return (VectorUtil::EmptyGiven<Cont>(c));
	}
};

#endif