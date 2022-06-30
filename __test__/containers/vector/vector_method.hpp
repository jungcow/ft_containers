#ifndef __VECTOR_METHOD_H__
#define __VECTOR_METHOD_H__

#include <string_view>
#include <type_traits>

#include "../../global/tester_result.hpp"
#include "../../global/tester_util.hpp"
#include "../../global/type.hpp"
#include "../base/given_base.hpp"
#include "../base/method_base.hpp"

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
class VectorUtil::EraseGiven : public Test::Base::GivenBase<Cont>
{
private:
	typedef typename Cont::iterator iterator;
	typedef typename Cont::const_iterator const_iterator;

public:
	EraseGiven(Cont& input) : Test::Base::GivenBase<Cont>(input) {}

	Test::TesterResult<iterator> when(iterator position)
	{
		return (Test::TesterUtil()
					.impl<Cont,
						  iterator,
						  const_iterator>(this->c, &Cont::erase, position));
	}
	Test::TesterResult<iterator> when(iterator first, iterator last)
	{
		return (Test::TesterUtil()
					.impl<Cont,
						  iterator,
						  const_iterator,
						  const_iterator>(this->c, &Cont::erase, first, last));
	}
};

class VectorMethod::Erase : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::EraseGiven<Cont> given(Cont& c)
	{
		return (VectorUtil::EraseGiven<Cont>(c));
	}
};

#endif
