#ifndef __VECTOR_END_H__
#define __VECTOR_END_H__

#include "../../global/tester_result.hpp"
#include "../../global/tester_util.hpp"
#include "../base/method_base.hpp"
#include "../base/vector_given_base.hpp"

#if TYPE
#include "type.hpp"
#endif

namespace Test
{
	namespace VectorMethod
	{
		class End;
		class EndConst;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class EndGiven;
		template <class Cont>
		class EndConstGiven;
	}
}

template <class Cont>
class Test::VectorUtil::EndGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	EndGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	Test::TesterResult<typename __base::iterator> when()
	{
		std::cout << "non-const when\n";
		return (Test::TesterUtil<typename __base::iterator>()
					.template impl<Cont>(this->c, &Cont::end));
	}
};

template <class Cont>
class Test::VectorUtil::EndConstGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	EndConstGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	Test::TesterResult<typename __base::const_iterator> when()
	{
		std::cout << "const when\n";
		return (Test::TesterUtil<typename __base::const_iterator>()
					.template impl<Cont>(this->c, &Cont::end));
	}
};

class Test::VectorMethod::End : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::EndGiven<Cont> given(Cont& c)
	{
		return VectorUtil::EndGiven<Cont>(c);
	}
};
class Test::VectorMethod::EndConst : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::EndConstGiven<Cont> given(Cont& c)
	{
		return VectorUtil::EndConstGiven<Cont>(c);
	}
};

#endif
