#ifndef __VECTOR_AT_H__
#define __VECTOR_AT_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/tester_util.hpp"

namespace Test
{
	namespace VectorMethod
	{
		class At;
		class AtConst;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class AtGiven;
		template <class Cont>
		class AtConstGiven;
	}
}

template <class Cont>
class Test::VectorUtil::AtGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	AtGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	// TODO: exception 관리
	Test::TesterResult<typename __base::reference> when(typename __base::size_type n)
	{
		std::cout << "non-const when\n";
		return (Test::TesterUtil<typename __base::reference>()
					.template impl<Cont,
								   typename __base::size_type>(this->c, &Cont::at, n));
	}
};
template <class Cont>
class Test::VectorUtil::AtConstGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	AtConstGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	// TODO: exception 관리
	Test::TesterResult<typename __base::const_reference> when(typename __base::size_type n)
	{
		std::cout << "const when\n";
		return (Test::TesterUtil<typename __base::const_reference>()
					.template impl<Cont,
								   typename __base::size_type>(this->c, &Cont::at, n));
	}
};

class Test::VectorMethod::At : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::AtGiven<Cont> given(Cont& container)
	{
		return VectorUtil::AtGiven<Cont>(container);
	}
};
class Test::VectorMethod::AtConst : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::AtConstGiven<Cont> given(Cont& container)
	{
		return VectorUtil::AtConstGiven<Cont>(container);
	}
};

#endif
