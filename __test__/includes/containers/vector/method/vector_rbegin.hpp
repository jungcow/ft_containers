#ifndef __VECTOR_RBEGIN_H__
#define __VECTOR_RBEGIN_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/tester_util.hpp"

namespace ContainerAssured
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
class ContainerAssured::VectorUtil::RBeginGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	RBeginGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	// TODO: UB 관리
	ContainerAssured::TesterResult<typename __base::reverse_iterator> when()
	{
		std::cout << "non-const when\n";
		return (ContainerAssured::When<typename __base::reverse_iterator>()
					.template impl<Cont>(this->c, &Cont::rbegin));
	}
};

template <class Cont>
class ContainerAssured::VectorUtil::RBeginConstGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	RBeginConstGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	// TODO: UB 관리
	ContainerAssured::TesterResult<typename __base::const_reverse_iterator> when()
	{
		std::cout << "const when\n";
		return (ContainerAssured::When<typename __base::const_reverse_iterator>()
					.template impl<Cont>(this->c, &Cont::rbegin));
	}
};

class ContainerAssured::VectorMethod::RBegin : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::RBeginGiven<Cont> given(Cont& container)
	{
		return VectorUtil::RBeginGiven<Cont>(container);
	}
};
class ContainerAssured::VectorMethod::RBeginConst : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::RBeginConstGiven<Cont> given(Cont& container)
	{
		return VectorUtil::RBeginConstGiven<Cont>(container);
	}
};

#endif
