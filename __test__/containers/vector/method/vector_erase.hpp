#ifndef __VECTOR_METHOD_H__
#define __VECTOR_METHOD_H__

#include "../../global/tester_result.hpp"
#include "../../global/tester_util.hpp"
#include "../../global/type.hpp"
#include "../base/method_base.hpp"
#include "../base/vector_given_base.hpp"

namespace Test
{
	namespace VectorMethod
	{
		class Erase;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class EraseGiven;
	}
}

template <class Cont>
class Test::VectorUtil::EraseGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	EraseGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	Test::TesterResult<typename __base::iterator> when(typename __base::iterator position)
	{
		return (Test::TesterUtil()
					.impl<Cont,
						  typename __base::iterator,
						  typename __base::const_iterator>(this->c, &Cont::erase, position));
	}
	Test::TesterResult<typename __base::iterator> when(typename __base::iterator first, typename __base::iterator last)
	{
		return (Test::TesterUtil()
					.impl<Cont,
						  typename __base::iterator,
						  typename __base::const_iterator,
						  typename __base::const_iterator>(this->c, &Cont::erase, first, last));
	}
};

class Test::VectorMethod::Erase : public Test::MethodBase
{
public:
	template <class Cont>
	Test::VectorUtil::EraseGiven<Cont> given(Cont& c)
	{
		return (VectorUtil::EraseGiven<Cont>(c));
	}
};

#endif
