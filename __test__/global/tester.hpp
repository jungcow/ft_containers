#ifndef __TESTER_H__
#define __TESTER_H__

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
