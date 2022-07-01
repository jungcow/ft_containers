#ifndef __VECTOR_FRONT_H__
#define __VECTOR_FRONT_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/tester_util.hpp"

namespace Test
{
	namespace VectorMethod
	{
		class Front;
		class FrontConst;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class FrontGiven;
		template <class Cont>
		class FrontConstGiven;
	}
}

template <class Cont>
class Test::VectorUtil::FrontGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	FrontGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	// TODO: UB 관리
	Test::TesterResult<typename __base::reference> when()
	{
		std::cout << "non-const when\n";
		return (Test::TesterUtil<typename __base::reference>()
					.template impl<Cont>(this->c, &Cont::front));
	}
};

template <class Cont>
class Test::VectorUtil::FrontConstGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	FrontConstGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	// TODO: UB 관리
	Test::TesterResult<typename __base::const_reference> when()
	{
		std::cout << "const when\n";
		return (Test::TesterUtil<typename __base::const_reference>()
					.template impl<Cont>(this->c, &Cont::front));
	}
};

class Test::VectorMethod::Front : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::FrontGiven<Cont> given(Cont& container)
	{
		return VectorUtil::FrontGiven<Cont>(container);
	}
};
class Test::VectorMethod::FrontConst : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::FrontConstGiven<Cont> given(Cont& container)
	{
		return VectorUtil::FrontConstGiven<Cont>(container);
	}
};

#endif
