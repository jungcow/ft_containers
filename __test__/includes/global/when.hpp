#ifndef __WHEN_H__
#define __WHEN_H__

#include <chrono>

#include "global/parameter_pack.hpp"
#include "global/tester_result.hpp"

namespace ContainerAssured
{
	// TODO: continaer's void specialization
	// TODO: container's and result's void specialization
	//============================ non-void ===============================
	template <class Result>
	class When
	{
	private:
		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point endTime;

	public:
		/**
		 * no parameter method
		 */
		template <class Cont>
		TesterResult<Cont, Result, voidParameterPack> impl(Cont& c, Result (Cont::*pm)())
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)();
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont, Result, voidParameterPack>(c, result, voidParameterPack(), this->endTime - this->startTime));
		}
		template <class Cont>
		TesterResult<Cont, Result, voidParameterPack> impl(Cont& c, Result (Cont::*pm)() const)
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)();
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont, Result, voidParameterPack>(c, result, voidParameterPack(), this->endTime - this->startTime));
		}
		/**
		 * one parameter method
		 */
		template <class Cont, class Arg>
		TesterResult<Cont,
					 Result, typename oneParameterPack<Arg>::type>
		impl(Cont& c, Result (Cont::*pm)(Arg), Arg arg)
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)(arg);
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont, Result, typename oneParameterPack<Arg>::type>(c, result, typename oneParameterPack<Arg>::type(arg), this->endTime - this->startTime));
		}
		template <class Cont, class Arg>
		TesterResult<Cont,
					 Result, typename oneParameterPack<Arg>::type>
		impl(Cont& c, Result (Cont::*pm)(Arg) const, Arg arg)
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)(arg);
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont, Result,
								 typename oneParameterPack<Arg>::type>(c,
																	   result,
																	   typename oneParameterPack<Arg>::type(arg),
																	   this->endTime - this->startTime));
		}
		/**
		 * two parameter method
		 */
		template <class Cont, class Arg1, class Arg2>
		TesterResult<Cont, Result, typename twoParameterPack<Arg1, Arg2>::type> impl(Cont& c, Result (Cont::*pm)(Arg1, Arg2), Arg1 arg1, Arg2 arg2)
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)(arg1, arg2);
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont, Result, typename twoParameterPack<Arg1, Arg2>::type>(c, result, typename twoParameterPack<Arg1, Arg2>::type(arg1, arg2), this->endTime - this->startTime));
		}
		template <class Cont, class Arg1, class Arg2>
		TesterResult<Cont, Result, typename twoParameterPack<Arg1, Arg2>::type> impl(Cont& c, Result (Cont::*pm)(Arg1, Arg2) const, Arg1 arg1, Arg2 arg2)
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)(arg1, arg2);
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont, Result, typename twoParameterPack<Arg1, Arg2>::type>(c, result, typename twoParameterPack<Arg1, Arg2>::type(arg1, arg2), this->endTime - this->startTime));
		}
		/**
		 * three parameter method
		 */
		template <class Cont, class Arg1, class Arg2, class Arg3>
		TesterResult<Cont, Result, typename threeParameterPack<Arg1, Arg2, Arg3>::type> impl(Cont& c, Result (Cont::*pm)(Arg1, Arg2, Arg3), Arg1 arg1, Arg2 arg2, Arg3 arg3)
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)(arg1, arg2, arg3);
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont, Result, typename threeParameterPack<Arg1, Arg2, Arg3>::type>(c, result, typename threeParameterPack<Arg1, Arg2, Arg3>::type(arg1, arg2, arg3), this->endTime - this->startTime));
		}
		template <class Cont, class Arg1, class Arg2, class Arg3>
		TesterResult<Cont, Result, typename threeParameterPack<Arg1, Arg2, Arg3>::type> impl(Cont& c, Result (Cont::*pm)(Arg1, Arg2, Arg3) const, Arg1 arg1, Arg2 arg2, Arg3 arg3)
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)(arg1, arg2, arg3);
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont, Result, typename threeParameterPack<Arg1, Arg2, Arg3>::type>(c, result, typename threeParameterPack<Arg1, Arg2, Arg3>::type(arg1, arg2, arg3), this->endTime - this->startTime));
		}
		/**
		 * four parameter method
		 */
		template <class Cont, class Arg1, class Arg2, class Arg3, class Arg4>
		TesterResult<Cont, Result, ParameterPack<Arg1, Arg2, Arg3, Arg4> > impl(Cont& c, Result (Cont::*pm)(Arg1, Arg2, Arg3, Arg4), Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)(arg1, arg2, arg3, arg4);
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont, Result, ParameterPack<Arg1, Arg2, Arg3, Arg4> >(c, result, ParameterPack<Arg1, Arg2, Arg3, Arg3>(arg1, arg2, arg3, arg4), this->endTime - this->startTime));
		}
		template <class Cont, class Arg1, class Arg2, class Arg3, class Arg4>
		TesterResult<Cont, Result, ParameterPack<Arg1, Arg2, Arg3, Arg4> > impl(Cont& c, Result (Cont::*pm)(Arg1, Arg2, Arg3, Arg4) const, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)(arg1, arg2, arg3, arg4);
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont, Result, ParameterPack<Arg1, Arg2, Arg3, Arg4> >(c, result, ParameterPack<Arg1, Arg2, Arg3, Arg3>(arg1, arg2, arg3, arg4), this->endTime - this->startTime));
		}
	};

	//============================ Result's void specialization ===============================
	template <>
	class When<void>
	{
	private:
		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point endTime;

	public:
		/**
		 * no parameter method
		 */
		template <class Cont>
		TesterResult<Cont, void, voidParameterPack> impl(Cont& c, void (Cont::*pm)())
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)();
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont,
								 void,
								 voidParameterPack>(c, voidParameterPack(), this->endTime - this->startTime));
		}
		template <class Cont>
		TesterResult<Cont, void, voidParameterPack> impl(Cont& c, void (Cont::*pm)() const)
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)();
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont,
								 void,
								 voidParameterPack>(c, voidParameterPack(), this->endTime - this->startTime));
		}
		/**
		 * one parameter method
		 */
		template <class Cont, class Arg>
		TesterResult<Cont, void, typename oneParameterPack<Arg>::type> impl(Cont& c, void (Cont::*pm)(Arg), Arg arg)
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)(arg);
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont, void,
								 typename oneParameterPack<Arg>::type>(c,
																	   typename oneParameterPack<Arg>::type(arg),
																	   this->endTime - this->startTime));
		}
		template <class Cont, class Arg>
		TesterResult<Cont, void, typename oneParameterPack<Arg>::type> impl(Cont& c, void (Cont::*pm)(Arg) const, Arg arg)
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)(arg);
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont, void,
								 typename oneParameterPack<Arg>::type>(c,
																	   typename oneParameterPack<Arg>::type(arg),
																	   this->endTime - this->startTime));
		}
		/**
		 * two parameter method
		 */
		template <class Cont, class Arg1, class Arg2>
		TesterResult<Cont, void, typename twoParameterPack<Arg1, Arg2>::type> impl(Cont& c, void (Cont::*pm)(Arg1, Arg2), Arg1 arg1, Arg2 arg2)
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)(arg1, arg2);
			this->endTime = std::chrono::steady_clock::now();
			return TesterResult<Cont,
								void,
								typename twoParameterPack<Arg1, Arg2>::type>(c, typename twoParameterPack<Arg1, Arg2>::type(arg1, arg2), this->endTime - this->startTime);
		}
		template <class Cont, class Arg1, class Arg2>
		TesterResult<Cont, void, typename twoParameterPack<Arg1, Arg2>::type> impl(Cont& c, void (Cont::*pm)(Arg1, Arg2) const, Arg1 arg1, Arg2 arg2)
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)(arg1, arg2);
			this->endTime = std::chrono::steady_clock::now();
			return TesterResult<Cont,
								void,
								typename twoParameterPack<Arg1, Arg2>::type>(c, typename twoParameterPack<Arg1, Arg2>::type(arg1, arg2), this->endTime - this->startTime);
		}
		/**
		 * three parameter method
		 */
		template <class Cont, class Arg1, class Arg2, class Arg3>
		TesterResult<Cont, void, typename threeParameterPack<Arg1, Arg2, Arg3>::type> impl(Cont& c, void (Cont::*pm)(Arg1, Arg2, Arg3), Arg1 arg1, Arg2 arg2, Arg3 arg3)
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)(arg1, arg2, arg3);
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont,
								 void,
								 typename threeParameterPack<Arg1, Arg2, Arg3>::type>(c, typename threeParameterPack<Arg1, Arg2, Arg3>::type(arg1, arg2, arg3), this->endTime - this->startTime));
		}
		template <class Cont, class Arg1, class Arg2, class Arg3>
		TesterResult<Cont, void, typename threeParameterPack<Arg1, Arg2, Arg3>::type> impl(Cont& c, void (Cont::*pm)(Arg1, Arg2, Arg3) const, Arg1 arg1, Arg2 arg2, Arg3 arg3)
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)(arg1, arg2, arg3);
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont,
								 void,
								 typename threeParameterPack<Arg1, Arg2, Arg3>::type>(c, typename threeParameterPack<Arg1, Arg2, Arg3>::type(arg1, arg2, arg3), this->endTime - this->startTime));
		}
		/**
		 * four parameter method
		 */
		template <class Cont, class Arg1, class Arg2, class Arg3, class Arg4>
		TesterResult<Cont, void, ParameterPack<Arg1, Arg2, Arg3, Arg4> > impl(Cont& c, void (Cont::*pm)(Arg1, Arg2, Arg3, Arg4), Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)(arg1, arg2, arg3, arg4);
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont,
								 void,
								 ParameterPack<Arg1, Arg2, Arg3, Arg4> >(c, ParameterPack<Arg1, Arg2, Arg3, Arg4>(arg1, arg2, arg3, arg4), this->endTime - this->startTime));
		}
		template <class Cont, class Arg1, class Arg2, class Arg3, class Arg4>
		TesterResult<Cont, void, ParameterPack<Arg1, Arg2, Arg3, Arg4> > impl(Cont& c, void (Cont::*pm)(Arg1, Arg2, Arg3, Arg4) const, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)(arg1, arg2, arg3, arg4);
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont,
								 void,
								 ParameterPack<Arg1, Arg2, Arg3, Arg4> >(c, ParameterPack<Arg1, Arg2, Arg3, Arg4>(arg1, arg2, arg3, arg4), this->endTime - this->startTime));
		}
	};
}

#endif
