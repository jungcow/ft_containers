#ifndef __VECTOR_RESIZE_H__
#define __VECTOR_RESIZE_H__

#include "../../global/tester_result.hpp"
#include "../../global/tester_util.hpp"
#include "../base/method_base.hpp"
#include "../base/vector_given_base.hpp"

namespace Test
{
	namespace VectorMethod
	{
		class Resize;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class ResizeGiven;
	}
}

template <class Cont>
class Test::VectorUtil::ResizeGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	ResizeGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	Test::TesterResult<void> when(typename __base::size_type n,
								  typename __base::value_type val = typename __base::value_type())
	{
		return (Test::TesterUtil<void>()
					.template impl<Cont,
								   typename __base::size_type,
								   typename __base::const_reference>(this->c, &Cont::resize, n, val));
	}
};

class Test::VectorMethod::Resize : public Test::MethodBase
{
public:
	template <class Cont>
	Test::VectorUtil::ResizeGiven<Cont> given(Cont& c)
	{
		return (VectorUtil::ResizeGiven<Cont>(c));
	}
};

#endif
