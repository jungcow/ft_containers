#ifndef __METHOD_BASE_H__
#define __METHOD_BASE_H__

#include <chrono>

#include "./given_base.hpp"

using namespace Test;

class MethodBase
{
public:
	template <class Cont>
	Base::GivenBase<Cont>* given(Cont c)
	{
		return new Base::GivenBase<Cont>(c);
	}
};

#endif
