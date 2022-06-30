#ifndef __VECTOR_PUSH_BACK_H__
#define __VECTOR_PUSH_BACK_H__

#include "../../global/tester_result.hpp"
#include "../../global/tester_util.hpp"
#include "../base/method_base.hpp"
#include "../base/vector_given_base.hpp"

namespace Test
{
	namespace VectorMethod
	{
		class PushBack;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class PushBackGiven;
	}
}

template <class Cont>
class Test::VectorUtil::PushBackGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	PushBackGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	Test::TesterResult<void> when(typename __base::const_reference val)
	{
		return (Test::TesterUtil<void>()
					.template impl<Cont,
								   typename __base::const_reference>(this->c, &Cont::push_back, val));
	}
};

class Test::VectorMethod::PushBack : public Test::MethodBase
{
public:
	template <class Cont>
	Test::VectorUtil::PushBackGiven<Cont> given(Cont& c)
	{
		return (VectorUtil::PushBackGiven<Cont>(c));
	}
};

#endif
