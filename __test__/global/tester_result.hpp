#ifndef __TESTER_RESULT_H__
#define __TESTER_RESULT_H__

#include <algorithm>
#include <chrono>

#include "tester_info.hpp"

namespace Test
{
	template <typename Result>
	class TesterResult : public TesterInfo
	{
	private:
		Result result;
		std::chrono::duration<double> sec;

	public:
		TesterResult(const Result& rs) : result(rs), sec(-1) {}
		TesterResult(const Result& rs, const std::chrono::duration<double>& timespan) : result(rs), sec(timespan) {}

		bool then(Result a)
		{
			if (result == a)
				return true;
			return false;
		}

		template <typename F>
		bool then_if(Result a, F pred)
		{
			return pred(a);
		}

		template <class timeunit = std::chrono::duration<double> >
		std::string info()
		{
			if (sec.count() < 0)
				return (std::string("This test doesn't check time duration"));
			return (TesterInfo::info(std::chrono::duration_cast<timeunit>(sec)));
		}
	};
}

#endif
