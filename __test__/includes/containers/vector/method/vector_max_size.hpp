#ifndef __VECTOR_MAX_SIZE_H__
#define __VECTOR_MAX_SIZE_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/tester_util.hpp"

namespace Test
{
	namespace VectorMethod
	{
		class MaxSize;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class MaxSizeGiven;
	}
}

template <class Cont>
class Test::VectorUtil::MaxSizeGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	MaxSizeGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	Test::TesterResult<typename __base::size_type> when()
	{
		return (Test::TesterUtil<typename __base::size_type>()
					.template impl<Cont>(this->c, &Cont::max_size));
	}
};

class Test::VectorMethod::MaxSize : public Test::MethodBase
{
public:
	template <class Cont>
	Test::VectorUtil::MaxSizeGiven<Cont> given(Cont& container)
	{
		return (VectorUtil::MaxSizeGiven<Cont>(container));
	}
};

#endif
