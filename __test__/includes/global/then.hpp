#ifndef __THEN_H__
#define __THEN_H__

#include "global/tester_type_traits.hpp"
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
	template <class Cont, class Result, class Args>
	class ThenBase : public TesterInfo
	{
	private:
		Cont container;
		const Args args;  // ParameterPack class
		std::chrono::duration<double> sec;
		std::string log;

	protected:
		ThenBase(const Cont& c, const Args& inputArgs, std::chrono::duration<double> timespan)
			: container(c), args(inputArgs), sec(timespan) {}

		ThenBase(const Args& inputArgs, std::chrono::duration<double> timespan)
			: args(inputArgs), sec(timespan) {}

	protected:
		template <class T = Args>
		typename T::Arg1Type firstParam(typename std::enable_if<!is_lt_one<T>::value>::type* = nullptr)
		{
			return args.firstParam();
		}

		template <class T = Args>
		typename T::Arg2Type secondParam(typename std::enable_if<!is_lt_two<T>::value>::type* = nullptr)
		{
			return args.secondParam();
		}

		template <class T = Args>
		typename T::Arg3Type thridParam(typename std::enable_if<!is_lt_three<T>::value>::type* = nullptr)
		{
			return args.thridParam();
		}

		template <class T = Args>
		typename T::Arg4Type fourthParam(typename std::enable_if<!is_lt_four<T>::value>::type* = nullptr)
		{
			return args.fourthParam();
		}

		const Cont& thisValue()
		{
			return container;
		}

	public:
		template <class timeunit = std::chrono::duration<double> >
		std::string info()
		{
			if (sec.count() < 0)
				return (std::string("This test doesn't check time duration"));
			return (TesterInfo::info(std::chrono::duration_cast<timeunit>(sec)));
		}
	};

	//=============================================================================
	template <class Cont, class Result, class Args>
	struct Then : public ThenBase<Cont, Result, Args>
	{
		Then(const Cont& c, const Result& rs, const Args& inputArgs, std::chrono::duration<double> timespan)
			: ThenBase<Cont, Result, Args>(c, inputArgs, timespan), result(rs) {}

		template <class T = Args>
		Then* assertFirstParam(typename std::enable_if<!is_lt_one<T>::value>::type* = nullptr)
		{
			this->firstParam();
			return this;
		}

		template <class T = Args>
		Then* assertSecondParam(typename std::enable_if<!is_lt_two<T>::value>::type* = nullptr)
		{
			this->secondParam();
			return this;
		}

		template <class T = Args>
		Then* assertThridParam(typename std::enable_if<!is_lt_three<T>::value>::type* = nullptr)
		{
			this->thridParam();
			return this;
		}

		template <class T = Args>
		Then* assertFourthParam(typename std::enable_if<!is_lt_four<T>::value>::type* = nullptr)
		{
			this->fourthParam();
			return this;
		}
		Then* assertThisValue()
		{
			this->thisValue();
			return this;
		}

		Then* assertReturnValue()
		{
			// result;
			return this;
		}

	private:
		const Result& result;
	};

	/**
	 * Cont의 void에 대한 특수화
	 */
	template <class Result, class Args>
	struct Then<void, Result, Args> : public ThenBase<int, Result, Args>
	{
		Then(const Result& rs, const Args& inputArgs, std::chrono::duration<double> timespan)
			: ThenBase<int, Result, Args>(inputArgs, timespan), result(rs) {}

		template <class T = Args>
		Then* assertFirstParam(typename std::enable_if<!is_lt_one<T>::value>::type* = nullptr)
		{
			this->firstParam();
			return this;
		}

		template <class T = Args>
		Then* assertSecondParam(typename std::enable_if<!is_lt_two<T>::value>::type* = nullptr)
		{
			this->secondParam();
			return this;
		}

		template <class T = Args>
		Then* assertThridParam(typename std::enable_if<!is_lt_three<T>::value>::type* = nullptr)
		{
			this->thridParam();
			return this;
		}

		template <class T = Args>
		Then* assertFourthParam(typename std::enable_if<!is_lt_four<T>::value>::type* = nullptr)
		{
			this->fourthParam();
			return this;
		}

		Then* assertReturnValue()
		{
			// result;
			return this;
		}

	private:
		const Result& result;
	};

	/**
	 * Result의 void에 대한 특수화
	 */
	template <class Cont, class Args>
	struct Then<Cont, void, Args> : public ThenBase<Cont, int, Args>
	{
		Then(const Cont& c, const Args& inputArgs, std::chrono::duration<double> timespan)
			: ThenBase<Cont, int, Args>(c, inputArgs, timespan) {}

		template <class T = Args>
		Then* assertFirstParam(typename std::enable_if<!is_lt_one<T>::value>::type* = nullptr)
		{
			this->firstParam();
			return this;
		}

		template <class T = Args>
		Then* assertSecondParam(typename std::enable_if<!is_lt_two<T>::value>::type* = nullptr)
		{
			this->secondParam();
			return this;
		}

		template <class T = Args>
		Then* assertThridParam(typename std::enable_if<!is_lt_three<T>::value>::type* = nullptr)
		{
			this->thridParam();
			return this;
		}

		template <class T = Args>
		Then* assertFourthParam(typename std::enable_if<!is_lt_four<T>::value>::type* = nullptr)
		{
			this->fourthParam();
			return this;
		}
		Then* assertThisValue()
		{
			this->thisValue();
			return this;
		}
	};

	/**
	 * Cont와 Result의 void에 대한 특수화
	 */
	template <class Args>
	struct Then<void, void, Args> : ThenBase<int, int, Args>
	{
		Then(const Args& inputArgs, std::chrono::duration<double> timespan)
			: ThenBase<int, int, Args>(inputArgs, timespan) {}

		template <class T = Args>
		Then* assertFirstParam(typename std::enable_if<!is_lt_one<T>::value>::type* = nullptr)
		{
			this->firstParam();
			return this;
		}

		template <class T = Args>
		Then* assertSecondParam(typename std::enable_if<!is_lt_two<T>::value>::type* = nullptr)
		{
			this->secondParam();
			return this;
		}

		template <class T = Args>
		Then* assertThridParam(typename std::enable_if<!is_lt_three<T>::value>::type* = nullptr)
		{
			this->thridParam();
			return this;
		}

		template <class T = Args>
		Then* assertFourthParam(typename std::enable_if<!is_lt_four<T>::value>::type* = nullptr)
		{
			this->fourthParam();
			return this;
		}
	};
}

#endif