#ifndef __VECTOR_BEGIN_H__
#define __VECTOR_BEGIN_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/tester_util.hpp"

namespace Test
{
	namespace VectorMethod
	{
		class Begin;
		class BeginConst;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class BeginGiven;
		template <class Cont>
		class BeginConstGiven;
	}
}

template <class Cont>
class Test::VectorUtil::BeginGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	BeginGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	// TODO: UB 관리
	Test::TesterResult<typename __base::iterator> when()
	{
		std::cout << "non-const when\n";
		return (Test::TesterUtil<typename __base::iterator>()
					.template impl<Cont>(this->c, &Cont::begin));
	}
};

template <class Cont>
class Test::VectorUtil::BeginConstGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	BeginConstGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	// TODO: UB 관리
	Test::TesterResult<typename __base::const_iterator> when()
	{
		std::cout << "const when\n";
		return (Test::TesterUtil<typename __base::const_iterator>()
					.template impl<Cont>(this->c, &Cont::begin));
	}
};

class Test::VectorMethod::Begin : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::BeginGiven<Cont> given(Cont& container)
	{
		return VectorUtil::BeginGiven<Cont>(container);
	}
};
class Test::VectorMethod::BeginConst : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::BeginConstGiven<Cont> given(Cont& container)
	{
		return VectorUtil::BeginConstGiven<Cont>(container);
	}
};

#endif
