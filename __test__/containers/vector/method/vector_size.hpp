#ifndef __VECTOR_SIZE_H__
#define __VECTOR_SIZE_H__

#include "../../global/tester_result.hpp"
#include "../../global/tester_util.hpp"
#include "../base/method_base.hpp"
#include "../base/vector_given_base.hpp"

namespace Test
{
	namespace VectorMethod
	{
		class Size;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class SizeGiven;
	}
}

template <class Cont>
class Test::VectorUtil::SizeGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	SizeGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	Test::TesterResult<typename __base::size_type> when()
	{
		return (Test::TesterUtil<typename __base::size_type>()
					.template impl<Cont>(this->c, &Cont::size));
	}
};

class Test::VectorMethod::Size : public Test::MethodBase
{
public:
	template <class Cont>
	Test::VectorUtil::SizeGiven<Cont> given(Cont& c)
	{
		return (VectorUtil::SizeGiven<Cont>(c));
	}
};

#endif