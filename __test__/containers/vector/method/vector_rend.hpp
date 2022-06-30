#ifndef __VECTOR_REND_H__
#define __VECTOR_REND_H__

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
		class REnd;
		class REndConst;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class REndGiven;
		template <class Cont>
		class REndConstGiven;
	}
}

template <class Cont>
class Test::VectorUtil::REndGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	REndGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	Test::TesterResult<typename __base::reverse_iterator> when()
	{
		std::cout << "non-const when\n";
		return (Test::TesterUtil<typename __base::reverse_iterator>()
					.template impl<Cont>(this->c, &Cont::rend));
	}
};

template <class Cont>
class Test::VectorUtil::REndConstGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	REndConstGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	Test::TesterResult<typename __base::const_reverse_iterator> when()
	{
		std::cout << "const when\n";
		return (Test::TesterUtil<typename __base::const_reverse_iterator>()
					.template impl<Cont>(this->c, &Cont::rend));
	}
};

class Test::VectorMethod::REnd : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::REndGiven<Cont> given(Cont& c)
	{
		return VectorUtil::REndGiven<Cont>(c);
	}
};
class Test::VectorMethod::REndConst : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::REndConstGiven<Cont> given(Cont& c)
	{
		return VectorUtil::REndConstGiven<Cont>(c);
	}
};

#endif
