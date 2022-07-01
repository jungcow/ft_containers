#ifndef __METHOD_BASE_H__
#define __METHOD_BASE_H__

#include <chrono>

#include "./vector_given_base.hpp"

namespace Test
{
	class MethodBase
	{
	public:
		template <class Cont>
		Test::Base::VectorGivenBase<Cont> given(Cont& container)
		{
			return Base::VectorGivenBase<Cont>(container);
		}
	};
}

#endif
