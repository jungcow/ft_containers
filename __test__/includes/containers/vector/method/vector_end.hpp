#ifndef __VECTOR_END_H__
#define __VECTOR_END_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/when.hpp"

namespace ContainerAssured
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
class ContainerAssured::VectorUtil::EndGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;
	const char* methodname = "end";

public:
	EndGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	ContainerAssured::TesterResult<Cont, typename __base::iterator, voidParameterPack>
	when()
	{
		return (ContainerAssured::When<typename __base::iterator>(methodname)
					.template impl<Cont>(this->c, &Cont::end));
	}
};

template <class Cont>
class ContainerAssured::VectorUtil::EndConstGiven : public ContainerAssured::Base::VectorGivenBase<Cont>
{
private:
	typedef ContainerAssured::Base::VectorGivenBase<Cont> __base;
	const char* methodname = "end const";

public:
	EndConstGiven(Cont& input) : ContainerAssured::Base::VectorGivenBase<Cont>(input) {}

	ContainerAssured::TesterResult<Cont, typename __base::const_iterator, voidParameterPack>
	when()
	{
		return (ContainerAssured::When<typename __base::const_iterator>(methodname)
					.template impl<Cont>(this->c, &Cont::end));
	}
};

class ContainerAssured::VectorMethod::End : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::EndGiven<Cont> given(Cont& container)
	{
		return VectorUtil::EndGiven<Cont>(container);
	}
};
class ContainerAssured::VectorMethod::EndConst : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::EndConstGiven<Cont> given(Cont& container)
	{
		return VectorUtil::EndConstGiven<Cont>(container);
	}
};

#endif
