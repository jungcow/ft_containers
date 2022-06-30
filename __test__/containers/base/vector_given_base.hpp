#ifndef __GIVEN_BASE_H__
#define __GIVEN_BASE_H__

#include <chrono>

namespace Test
{
	namespace Base
	{
		template <class Cont>
		class VectorGivenBase
		{
		protected:
			Cont& c;

			typedef typename Cont::value_type value_type;
			typedef typename Cont::reference reference;
			typedef typename Cont::const_reference const_reference;
			typedef typename Cont::pointer pointer;
			typedef typename Cont::const_pointer const_pointer;
			typedef typename Cont::iterator iterator;
			typedef typename Cont::const_iterator const_iterator;
			typedef typename Cont::reverse_iterator reverse_iterator;
			typedef typename Cont::const_reverse_iterator const_reverse_iterator;
			typedef typename Cont::difference_type difference_type;
			typedef typename Cont::size_type size_type;

		public:
			VectorGivenBase(Cont& input) : c(input) {}
			void when()
			{
				std::cout << "it's default when method in GivenBase class" << std::endl;
			}
		};
	}
}

#endif
