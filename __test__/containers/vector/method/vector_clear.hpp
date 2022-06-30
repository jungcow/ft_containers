#ifndef __VECTOR_CLEAR_H__
#define __VECTOR_CLEAR_H__

#include "../../global/tester_result.hpp"
#include "../../global/tester_util.hpp"
#include "../base/method_base.hpp"
#include "../base/vector_given_base.hpp"

namespace Test
{
	namespace VectorMethod
	{
		class Clear;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class ClearGiven;
	}
}

template <class Cont>
class Test::VectorUtil::ClearGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	ClearGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	Test::TesterResult<void> when()
	{
		return (Test::TesterUtil<void>()
					.template impl<Cont>(this->c, &Cont::clear));
	}
};

class Test::VectorMethod::Clear : public Test::MethodBase
{
public:
	template <class Cont>
	Test::VectorUtil::ClearGiven<Cont> given(Cont& c)
	{
		return (VectorUtil::ClearGiven<Cont>(c));
	}
};

#endif
