#ifndef __THEN_H__
#define __THEN_H__

#include "tester_info.hpp"
#include "type.hpp"

namespace ContainerAssured
{
	/**
	 * Then Base Class
	 *
	 * Interface:
	 * - firstParam
	 * - secondParam
	 * - thirdParam
	 * - fourthParam
	 * - thisValue
	 * - returnValue
	 * - log
	 */
	// template <class Cont, class result, class Args>
	// class ThenBase
	// {
	// private:
	// 	const Result& result;
	// 	const Cont& container;
	// 	const Args args;  // ParameterPack class
	// 	std::chrono::duration<double> sec;
	// 	std::string log;
	// };

	//=============================================================================
	template <class Cont, class Result, class Args>
	class Then : public TesterInfo
	{
	private:
		const Result& result;
		const Cont& container;
		const Args args;  // ParameterPack class
		std::chrono::duration<double> sec;
		std::string log;

	public:
		Then(const Cont& c, const Result& rs, const Args& inputArgs, std::chrono::duration<double> timespan)
			: container(c), result(rs), args(inputArgs), sec(timespan) {}
		// template <>
		Then* firstParam()
		{
			if (Args::num < 1)
				std::cout << "no param\n";
			else
				std::cout << "first param: " << args.firstParam() << '\n';
			return this;
		}
		Then* thisValue()
		{
			std::cout << "then's container addresss: " << &container << std::endl;
		}
		Then* returnValue()
		{
			std::cout << "then's return value: " << result << std::endl;
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
	class Then<void, Result, Args> : TesterInfo
	{
	private:
		const Result& result;
		const Args args;  // ParameterPack class
		std::chrono::duration<double> sec;
		std::string log;

	public:
		Then(const Result& rs, const Args& inputArgs, std::chrono::duration<double> timespan)
			: result(rs), args(inputArgs), sec(timespan) {}
		// template <>
		Then* firstParam()
		{
			if (Args::num < 1)
				std::cout << "no param\n";
			else
			{
				std::cout << "first param: " << args.firstParam() << '\n';
			}
			return this;
		}
		Then* returnValue()
		{
			std::cout << "then's return value: " << result << std::endl;
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
	class Then<Cont, void, Args> : TesterInfo
	{
	private:
		const Cont& container;
		const Args args;  // ParameterPack class
		std::chrono::duration<double> sec;
		std::string log;

	public:
		Then(const Cont& c, const Args& inputArgs, std::chrono::duration<double> timespan)
			: container(c), args(inputArgs), sec(timespan) {}
		// template <>
		Then* firstParam()
		{
			if (Args::num < 1)
				std::cout << "no param\n";
			else
			{
				std::cout << "first param: " << args.firstParam() << '\n';
			}
			return this;
		}
		Then* thisValue()
		{
			std::cout << "then's container addresss: " << &container << std::endl;
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
	class Then<void, void, Args> : TesterInfo
	{
	private:
		const Args args;  // ParameterPack class
		std::chrono::duration<double> sec;
		std::string log;

	public:
		Then(const Args& inputArgs, std::chrono::duration<double> timespan)
			: args(inputArgs), sec(timespan) {}
		// template <>
		Then* firstParam()
		{
			if (Args::num < 1)
				std::cout << "no param\n";
			else
			{
				std::cout << "first param: " << args.firstParam() << '\n';
			}
			return this;
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