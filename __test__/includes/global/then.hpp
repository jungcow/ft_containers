#ifndef __THEN_H__
#define __THEN_H__

#include "assert.hpp"
#include "global/tester_type_traits.hpp"
#include "tester_info.hpp"
#include "then_base.hpp"
#include "type.hpp"

namespace ContainerAssured
{

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
			return AssertContainer<Then*, const Cont&>(this, this->assertInfo, container);
		}

		AssertReturnValue<Then*, const Result&, const Cont&> assertReturnValue()
		{
			return AssertReturnValue<Then*, const Result&, const Cont&>(this, this->assertInfo, result, container);
		}

	private:
		const Result& result;
		const Cont& container;
	};

#if 0
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
#endif
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
			return AssertContainer<Then*, Cont>(this, this->assertInfo, container);
		}

	private:
		const Cont& container;
	};

#if 0
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
#endif
}

#endif