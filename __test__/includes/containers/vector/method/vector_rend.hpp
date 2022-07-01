#ifndef __VECTOR_REND_H__
#define __VECTOR_REND_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/tester_util.hpp"

namespace ContainerAssured
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
class ContainerAssured::VectorUtil::REndGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	REndGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	ContainerAssured::TesterResult<Cont, typename __base::reverse_iterator,
								   ParameterPack<void, void, void, void> >
	when()
	{
		return (ContainerAssured::When<typename __base::reverse_iterator>()
					.template impl<Cont>(this->c, &Cont::rend));
	}
};

template <class Cont>
class ContainerAssured::VectorUtil::REndConstGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;

public:
	REndConstGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	ContainerAssured::TesterResult<Cont, typename __base::const_reverse_iterator,
								   ParameterPack<void, void, void, void> >
	when()
	{
		return (ContainerAssured::When<typename __base::const_reverse_iterator>()
					.template impl<Cont>(this->c, &Cont::rend));
	}
};

class ContainerAssured::VectorMethod::REnd : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::REndGiven<Cont> given(Cont& container)
	{
		return VectorUtil::REndGiven<Cont>(container);
	}
};
class ContainerAssured::VectorMethod::REndConst : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::REndConstGiven<Cont> given(Cont& container)
	{
		return VectorUtil::REndConstGiven<Cont>(container);
	}
};

#endif
