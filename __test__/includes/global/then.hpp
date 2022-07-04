#ifndef __THEN_H__
#define __THEN_H__

#include "assert.hpp"
#include "global/tester_type_traits.hpp"
#include "tester_info.hpp"
#include "type.hpp"

namespace ContainerAssured
{
	template <class Args>
	class ThenBase : public TesterInfo
	{
	private:
		const Args args;  // ParameterPack class
		std::chrono::duration<double> sec;

	protected:
		ContainerAssertInfo containerAssertInfo;
		ReturnValueAssertInfo returnValueAssertInfo;
		ParameterAssertInfo parameterAssertInfo;
		const char* methodname;

	protected:
		ThenBase(const Args& inputArgs, std::chrono::duration<double> timespan, const char* mn)
			: args(inputArgs), sec(timespan), methodname(mn) {}

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

	public:
		template <class timeunit = std::chrono::duration<double> >
		std::string info()
		{
			/**
			 * mmethod name
			 * assertion type
			 * assert name
			 * description
			 * result(bool)
			 */
			std::cout << "[ " << methodname << " ]" << std::endl;
			std::cout << containerAssertInfo.AssertName << std::endl;
			for (int i = 0; i < containerAssertInfo.assertions.size(); i++)
			{
				std::cout << containerAssertInfo.assertions[i].testname << " | ";
				std::cout << containerAssertInfo.assertions[i].description << " | ";
				if (containerAssertInfo.assertions[i].result == true)
					std::cout << "✅" << std::endl;
				else
					std::cout << "❌" << std::endl;
			}
			for (int i = 0; i < returnValueAssertInfo.assertions.size(); i++)
			{
				std::cout << returnValueAssertInfo.assertions[i].testname << " | ";
				std::cout << returnValueAssertInfo.assertions[i].description << " | ";
				if (returnValueAssertInfo.assertions[i].result == true)
					std::cout << "✅" << std::endl;
				else
					std::cout << "❌" << std::endl;
			}
			return ("");
			// if (sec.count() < 0)
			// 	return (std::string("This test doesn't check time duration"));
			// return (TesterInfo::info(std::chrono::duration_cast<timeunit>(sec)));
		}
	};

	//=============================================================================
	template <class Cont, class Result, class Args>
	struct Then : public ThenBase<Args>
	{
		Then(const Cont& c, const Result& rs, const Args& inputArgs, std::chrono::duration<double> timespan, const char* mn)
			: ThenBase<Args>(inputArgs, timespan, mn), container(c), result(rs) {}

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
		AssertContainer<Then*, const Cont&> assertContainer()
		{
			return AssertContainer<Then*, const Cont&>(this, this->containerAssertInfo, container);
		}

		AssertReturnValue<Then*, const Result&, const Cont&> assertReturnValue()
		{
			return AssertReturnValue<Then*, const Result&, const Cont&>(this, this->returnValueAssertInfo, result, container);
		}

	private:
		const Result& result;
		const Cont& container;
	};

	/**
	 * Cont의 void에 대한 특수화
	 */
	template <class Result, class Args>
	struct Then<void, Result, Args> : public ThenBase<Args>
	{
		Then(const Result& rs, const Args& inputArgs, std::chrono::duration<double> timespan, const char* mn)
			: ThenBase<Args>(inputArgs, timespan, mn), result(rs) {}

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

		// AssertReturnValue<Then*, Result&> assertReturnValue()
		// {
		// 	return AssertReturnValue<Then*, Result&>(this, this->returnValueAssertInfo, result);
		// }

	private:
		const Result& result;
	};

	/**
	 * Result의 void에 대한 특수화
	 */
	template <class Cont, class Args>
	struct Then<Cont, void, Args> : public ThenBase<Args>
	{
		Then(const Cont& c, const Args& inputArgs, std::chrono::duration<double> timespan, const char* mn)
			: ThenBase<Args>(inputArgs, timespan, mn), container(c) {}

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

		AssertContainer<Then*, Cont> assertContainer()
		{
			return AssertContainer<Then*, Cont>(this, this->containerAssertInfo, container);
		}

	private:
		const Cont& container;
	};

	/**
	 * Cont와 Result의 void에 대한 특수화
	 */
	template <class Args>
	struct Then<void, void, Args> : ThenBase<Args>
	{
		Then(const Args& inputArgs, std::chrono::duration<double> timespan, const char* mn)
			: ThenBase<Args>(inputArgs, timespan, mn) {}

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