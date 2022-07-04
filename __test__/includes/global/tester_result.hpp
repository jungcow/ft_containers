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
		const Result result;
		const Cont& container;
		const Args args;
		const char* methodname;
		std::chrono::duration<double> sec;

	public:
		TesterResult(const Cont& c, const Result& rs, const Args& inputArgs, const char* mn)
			: container(c), result(rs), args(inputArgs), sec(-1), methodname(mn) {}

		TesterResult(const Cont& c, const Result& rs, const Args& inputArgs, const std::chrono::duration<double>& timespan, const char* mn)
			: container(c), result(rs), args(inputArgs), sec(timespan), methodname(mn) {}

		Then<Cont, Result, Args>* then()
		{
			return (new Then<Cont, Result, Args>(container, result, args, sec, methodname));
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
		const char* methodname;
		std::chrono::duration<double> sec;

	public:
		TesterResult(const Result& rs, const Args& inputArgs, const char* mn)
			: result(rs), args(inputArgs), sec(-1), methodname(mn) {}

		TesterResult(const Result& rs, const Args& inputArgs, const std::chrono::duration<double>& timespan, const char* mn)
			: result(rs), args(inputArgs), sec(timespan), methodname(mn) {}

		Then<void, Result, Args>* then()
		{
			return (new Then<void, Result, Args>(result, args, sec, methodname));
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
		const char* methodname;
		std::chrono::duration<double> sec;

	public:
		TesterResult(const Cont& c, const Args& inputArgs, const char* mn) : container(c), args(inputArgs), sec(-1), methodname(mn) {}
		TesterResult(const Cont& c, const Args& inputArgs, const std::chrono::duration<double>& timespan, const char* mn)
			: container(c), args(inputArgs), sec(timespan), methodname(mn) {}

		Then<Cont, void, Args>* then()
		{
			return (new Then<Cont, void, Args>(container, args, sec, methodname));
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
		const char* methodname;
		std::chrono::duration<double> sec;

	public:
		TesterResult(const Args& inputArgs, const char* mn) : args(inputArgs), sec(-1), methodname(mn) {}
		TesterResult(const Args& inputArgs, const std::chrono::duration<double>& timespan, const char* mn) : args(inputArgs), sec(timespan), methodname(mn) {}

		Then<void, void, Args>* then()
		{
			return (new Then<void, void, Args>(args, sec, methodname));
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
