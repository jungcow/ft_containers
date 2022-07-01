#ifndef __TESTER_H__
#define __TESTER_H__

#include "vector/vector_tester.hpp"
#if 0
#include "map/map_tester.hpp"
#include "set/set_tester.hpp"
#include "stack/stack_tester.hpp"
#endif

namespace Test
{
	template <class TesterClass>
	class Tester
	{
	private:
		TesterClass* tester;

	public:
		Tester()
		{
			tester = new TesterClass();
		}
		~Tester()
		{
			delete tester;
		}

		TesterClass* operator->()
		{
			return tester;
		}
	};
}

#endif
