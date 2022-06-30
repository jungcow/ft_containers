#ifndef __TESTER_UTIL_H__
#define __TESTER_UTIL_H__

#include <chrono>
#include <iostream>

#include "tester_result.hpp"

namespace Test
{
	template <class Result>
	class TesterUtil
	{
	private:
		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point endTime;

	public:
		//============================ non-void ===============================
		template <class Cont>
		Test::TesterResult<Result> impl(Cont& c, Result (Cont::*pm)())
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)();
			this->endTime = std::chrono::steady_clock::now();
			return (Test::TesterResult<Result>(result, this->endTime - this->startTime));
		}
		template <class Cont>
		Test::TesterResult<Result> impl(Cont& c, Result (Cont::*pm)() const)
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)();
			this->endTime = std::chrono::steady_clock::now();
			return (Test::TesterResult<Result>(result, this->endTime - this->startTime));
		}

		/**
		 * method with one parameter(1)
		 * const method with one parameter(2)
		 */
		template <class Cont, class Arg>
		Test::TesterResult<Result> impl(Cont& c, Result (Cont::*pm)(Arg), Arg a)
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)(a);
			this->endTime = std::chrono::steady_clock::now();
			return (Test::TesterResult<Result>(result, this->endTime - this->startTime));
		}
		template <class Cont, class Arg>
		Test::TesterResult<Result> impl(Cont& c, Result (Cont::*pm)(Arg) const, Arg a)
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)(a);
			this->endTime = std::chrono::steady_clock::now();
			return (Test::TesterResult<Result>(result, this->endTime - this->startTime));
		}

		/**
		 * method with two parameter(1)
		 * const method with two parameter(2)
		 */
		template <class Cont, class Arg1, class Arg2>
		Test::TesterResult<Result> impl(Cont& c, Result (Cont::*pm)(Arg1, Arg2), Arg1 a1, Arg2 a2)
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)(a1, a2);
			this->endTime = std::chrono::steady_clock::now();
			return (Test::TesterResult<Result>(result, this->endTime - this->startTime));
		}
		template <class Cont, class Arg1, class Arg2>
		Test::TesterResult<Result> impl(Cont& c, Result (Cont::*pm)(Arg1, Arg2) const, Arg1 a1, Arg2 a2)
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)(a1, a2);
			this->endTime = std::chrono::steady_clock::now();
			return (Test::TesterResult<Result>(result, this->endTime - this->startTime));
		}
	};
	template <>
	class TesterUtil<void>
	{
	private:
		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point endTime;

	public:
		//============================ void ===============================
		/**
		 * method with no parameter(1)
		 * const method with no parameter(2)
		 */
		template <class Cont>
		Test::TesterResult<void> impl(Cont& c, void (Cont::*pm)())
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)();
			this->endTime = std::chrono::steady_clock::now();
			return (Test::TesterResult<void>(this->endTime - this->startTime));
		}
		template <class Cont>
		Test::TesterResult<void> impl(Cont& c, void (Cont::*pm)() const)
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)();
			this->endTime = std::chrono::steady_clock::now();
			return (Test::TesterResult<void>(this->endTime - this->startTime));
		}

		/**
		 * method with one parameter(1)
		 * const method with one parameter(2)
		 */
		template <class Cont, class Arg>
		Test::TesterResult<void> impl(Cont& c, void (Cont::*pm)(Arg), Arg a)
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)(a);
			this->endTime = std::chrono::steady_clock::now();
			return (Test::TesterResult<void>(this->endTime - this->startTime));
		}
		template <class Cont, class Arg>
		Test::TesterResult<void> impl(Cont& c, void (Cont::*pm)(Arg) const, Arg a)
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)(a);
			this->endTime = std::chrono::steady_clock::now();
			return (Test::TesterResult<void>(this->endTime - this->startTime));
		}

		/**
		 * method with two parameter(1)
		 * const method with two parameter(2)
		 */
		template <class Cont, class Arg1, class Arg2>
		Test::TesterResult<void> impl(Cont& c, void (Cont::*pm)(Arg1, Arg2), Arg1 a1, Arg2 a2)
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)(a1, a2);
			this->endTime = std::chrono::steady_clock::now();
			return (Test::TesterResult<void>(this->endTime - this->startTime));
		}
		template <class Cont, class Arg1, class Arg2>
		Test::TesterResult<void> impl(Cont& c, void (Cont::*pm)(Arg1, Arg2) const, Arg1 a1, Arg2 a2)
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)(a1, a2);
			this->endTime = std::chrono::steady_clock::now();
			return (Test::TesterResult<void>(this->endTime - this->startTime));
		}
	};
}

#endif
