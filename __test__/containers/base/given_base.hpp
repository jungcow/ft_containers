#ifndef __GIVEN_BASE_H__
#define __GIVEN_BASE_H__

#include <chrono>

namespace Test
{
	namespace Base
	{
		template <class Cont>
		class GivenBase
		{
		protected:
			Cont& c;

		public:
			GivenBase(Cont& input) : c(input) {}
			void when()
			{
				std::cout << "it's default when method in GivenBase class" << std::endl;
			}
		};
	}
}

#endif
