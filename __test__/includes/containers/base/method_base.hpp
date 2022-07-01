#ifndef __METHOD_BASE_H__
#define __METHOD_BASE_H__

#include <chrono>

#include "./vector_given_base.hpp"

namespace ContainerAssured
{
	class MethodBase
	{
	public:
		template <class Cont>
		ContainerAssured::Base::VectorGivenBase<Cont> given(Cont& container)
		{
			return Base::VectorGivenBase<Cont>(container);
		}
	};
}

#endif
