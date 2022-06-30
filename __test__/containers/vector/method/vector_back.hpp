#ifndef __VECTOR_BACK_H__
#define __VECTOR_BACK_H__

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
		class Back;
		class BackConst;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class BackGiven;
		template <class Cont>
		class BackConstGiven;
	}
}

template <class Cont>
class Test::VectorUtil::BackGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	BackGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	// TODO: UB 관리
	Test::TesterResult<typename __base::reference> when()
	{
		std::cout << "non-const when\n";
		return (Test::TesterUtil<typename __base::reference>()
					.template impl<Cont>(this->c, &Cont::back));
	}
};

template <class Cont>
class Test::VectorUtil::BackConstGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	BackConstGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	// TODO: UB 관리
	Test::TesterResult<typename __base::const_reference> when()
	{
		std::cout << "const when\n";
		return (Test::TesterUtil<typename __base::const_reference>()
					.template impl<Cont>(this->c, &Cont::back));
	}
};

class Test::VectorMethod::Back : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::BackGiven<Cont> given(Cont& c)
	{
		return VectorUtil::BackGiven<Cont>(c);
	}
};
class Test::VectorMethod::BackConst : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::BackConstGiven<Cont> given(Cont& c)
	{
		return VectorUtil::BackConstGiven<Cont>(c);
	}
};

#endif
