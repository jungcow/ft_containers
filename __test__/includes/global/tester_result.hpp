#ifndef __TESTER_RESULT_H__
#define __TESTER_RESULT_H__

#include <algorithm>
#include <chrono>

#include "tester_info.hpp"
#include "then.hpp"

namespace ContainerAssured
{
	/**
	 * First Template Parameter: Container Type
	 * Second Template Parameter: Return type
	 * Thrid Template Parameter: ParameterPack class Template
	 */
	template <class Cont, class Result, class Args>
	class TesterResult : public TesterInfo
	{
	private:
		const Result& result;
		const Cont& container;
		const Args args;
		std::chrono::duration<double> sec;

	public:
		TesterResult(const Cont& c, const Result& rs, const Args& inputArgs)
			: container(c), result(rs), args(inputArgs), sec(-1) {}

		TesterResult(const Cont& c, const Result& rs, const Args& inputArgs, const std::chrono::duration<double>& timespan)
			: container(c), result(rs), args(inputArgs), sec(timespan) {}

		Then<Cont, Result, Args>* then()
		{
			return (new Then<Cont, Result, Args>(container, result, args, sec));
		}

		template <class timeunit = std::chrono::duration<double> >
		std::string info()
		{
			if (sec.count() < 0)
				return (std::string("This test doesn't check time duration"));
			return (TesterInfo::info(std::chrono::duration_cast<timeunit>(sec)));
		}
	};

	/**
	 * Cont의 void에 대한 특수화
	 */
	template <class Result, class Args>
	class TesterResult<void, Result, Args> : public TesterInfo
	{
	private:
		const Result& result;
		const Args args;
		std::chrono::duration<double> sec;
		std::string log;

	public:
		TesterResult(const Result& rs, const Args& inputArgs)
			: result(rs), args(inputArgs), sec(-1) {}

		TesterResult(const Result& rs, const Args& inputArgs, const std::chrono::duration<double>& timespan)
			: result(rs), args(inputArgs), sec(timespan) {}

		Then<void, Result, Args>* then()
		{
			return (new Then<void, Result, Args>(result, args, sec));
		}

		template <class timeunit = std::chrono::duration<double> >
		std::string info()
		{
			if (sec.count() < 0)
				return (std::string("This test doesn't check time duration"));
			return (TesterInfo::info(std::chrono::duration_cast<timeunit>(sec)));
		}
	};

	/**
	 * Result의 void에 대한 특수화
	 */
	template <class Cont, class Args>
	class TesterResult<Cont, void, Args> : public TesterInfo
	{
	private:
		const Cont& container;
		const Args args;
		std::chrono::duration<double> sec;
		std::string log;

	public:
		TesterResult(const Cont& c, const Args& inputArgs) : container(c), args(inputArgs), sec(-1) {}
		TesterResult(const Cont& c, const Args& inputArgs, const std::chrono::duration<double>& timespan)
			: container(c), args(inputArgs), sec(timespan) {}

		Then<Cont, void, Args>* then()
		{
			return (new Then<Cont, void, Args>(container, args, sec));
		}

		template <class timeunit = std::chrono::duration<double> >
		std::string info()
		{
			if (sec.count() < 0)
				return (std::string("This test doesn't check time duration"));
			return (TesterInfo::info(std::chrono::duration_cast<timeunit>(sec)));
		}
	};

	/**
	 * Cont와 Result의 void에 대한 특수화
	 */
	template <class Args>
	class TesterResult<void, void, Args> : public TesterInfo
	{
	private:
		const Args args;
		std::chrono::duration<double> sec;
		std::string log;

	public:
		TesterResult(const Args& inputArgs) : args(inputArgs), sec(-1) {}
		TesterResult(const Args& inputArgs, const std::chrono::duration<double>& timespan) : args(inputArgs), sec(timespan) {}

		Then<void, void, Args>* then()
		{
			return (new Then<void, void, Args>(args, sec));
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
