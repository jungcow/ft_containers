#ifndef __VECTOR_RBEGIN_H__
#define __VECTOR_RBEGIN_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/tester_util.hpp"

namespace Test
{
	namespace VectorMethod
	{
		class RBegin;
		class RBeginConst;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class RBeginGiven;
		template <class Cont>
		class RBeginConstGiven;
	}
}

template <class Cont>
class Test::VectorUtil::RBeginGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	RBeginGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	// TODO: UB 관리
	Test::TesterResult<typename __base::reverse_iterator> when()
	{
		std::cout << "non-const when\n";
		return (Test::TesterUtil<typename __base::reverse_iterator>()
					.template impl<Cont>(this->c, &Cont::rbegin));
	}
};

template <class Cont>
class Test::VectorUtil::RBeginConstGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	RBeginConstGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	// TODO: UB 관리
	Test::TesterResult<typename __base::const_reverse_iterator> when()
	{
		std::cout << "const when\n";
		return (Test::TesterUtil<typename __base::const_reverse_iterator>()
					.template impl<Cont>(this->c, &Cont::rbegin));
	}
};

class Test::VectorMethod::RBegin : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::RBeginGiven<Cont> given(Cont& container)
	{
		return VectorUtil::RBeginGiven<Cont>(container);
	}
};
class Test::VectorMethod::RBeginConst : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::RBeginConstGiven<Cont> given(Cont& container)
	{
		return VectorUtil::RBeginConstGiven<Cont>(container);
	}
};

#endif
