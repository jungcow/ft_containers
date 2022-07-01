#ifndef __VECTOR_POP_BACK_H__
#define __VECTOR_POP_BACK_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/tester_util.hpp"

namespace Test
{
	namespace VectorMethod
	{
		class PopBack;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class PopBackGiven;
	}
}

template <class Cont>
class Test::VectorUtil::PopBackGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	PopBackGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	Test::TesterResult<void> when()
	{
		return (Test::TesterUtil<void>()
					.template impl<Cont>(this->c, &Cont::pop_back));
	}
};

class Test::VectorMethod::PopBack : public Test::MethodBase
{
public:
	template <class Cont>
	Test::VectorUtil::PopBackGiven<Cont> given(Cont& container)
	{
		return (VectorUtil::PopBackGiven<Cont>(container));
	}
};

#endif
