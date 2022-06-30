#ifndef __TESTER_UTIL_H__
#define __TESTER_UTIL_H__

#include <chrono>
#include <iostream>

#include "tester_result.hpp"

//============================ non-void ===============================
namespace Test
{
	template <class Result>
	class TesterUtil
	{
	private:
		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point endTime;

	public:
		template <class Cont, class... Args>
		Test::TesterResult<Result> impl(Cont& c, Result (Cont::*pm)(Args...), Args... args)
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)(args...);
			this->endTime = std::chrono::steady_clock::now();
			return (Test::TesterResult<Result>(result, this->endTime - this->startTime));
		}
		template <class Cont, class... Args>
		Test::TesterResult<Result> impl(Cont& c, Result (Cont::*pm)(Args...) const, Args... args)
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)(args...);
			this->endTime = std::chrono::steady_clock::now();
			return (Test::TesterResult<Result>(result, this->endTime - this->startTime));
		}
	};

	//============================ void specialization ===============================
	template <>
	class TesterUtil<void>
	{
	private:
		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point endTime;

	public:
		template <class Cont, class... Args>
		Test::TesterResult<void> impl(Cont& c, void (Cont::*pm)(Args...), Args... args)
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)(args...);
			this->endTime = std::chrono::steady_clock::now();
			return (Test::TesterResult<void>(this->endTime - this->startTime));
		}
		template <class Cont, class... Args>
		Test::TesterResult<void> impl(Cont& c, void (Cont::*pm)(Args...) const, Args... args)
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)(args...);
			this->endTime = std::chrono::steady_clock::now();
			return (Test::TesterResult<void>(this->endTime - this->startTime));
		}
	};
}

#endif
