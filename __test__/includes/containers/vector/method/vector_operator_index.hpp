#ifndef __VECTOR_OPERATOR_INDEX_H__
#define __VECTOR_OPERATOR_INDEX_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/tester_util.hpp"

namespace Test
{
	namespace VectorMethod
	{
		class OperatorIndex;
		class OperatorIndexConst;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class OperatorIndexGiven;
		template <class Cont>
		class OperatorIndexConstGiven;
	}
}

template <class Cont>
class Test::VectorUtil::OperatorIndexGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	OperatorIndexGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	// TODO: UB 관리
	Test::TesterResult<typename __base::reference> when(typename __base::size_type n)
	{
		std::cout << "non-const when\n";
		return (Test::TesterUtil<typename __base::reference>()
					.template impl<Cont,
								   typename __base::size_type>(this->c, &Cont::operator[], n));
	}
};

template <class Cont>
class Test::VectorUtil::OperatorIndexConstGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	OperatorIndexConstGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	// TODO: UB 관리
	Test::TesterResult<typename __base::const_reference> when(typename __base::size_type n)
	{
		std::cout << "const when\n";
		return (Test::TesterUtil<typename __base::const_reference>()
					.template impl<Cont,
								   typename __base::size_type>(this->c, &Cont::operator[], n));
	}
};

class Test::VectorMethod::OperatorIndex : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::OperatorIndexGiven<Cont> given(Cont& container)
	{
		return VectorUtil::OperatorIndexGiven<Cont>(container);
	}
};
class Test::VectorMethod::OperatorIndexConst : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::OperatorIndexConstGiven<Cont> given(Cont& container)
	{
		return VectorUtil::OperatorIndexConstGiven<Cont>(container);
	}
};

#endif
