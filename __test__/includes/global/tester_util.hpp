#ifndef __TESTER_UTIL_H__
#define __TESTER_UTIL_H__

#include <chrono>
#include <iostream>

#include "global/parameter_pack.hpp"
#include "global/tester_result.hpp"

namespace ContainerAssured
{
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
		TesterResult<Cont, Result, ParameterPack<void, void, void, void> > impl(Cont& c, Result (Cont::*pm)())
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)();
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont, Result, ParameterPack<void, void, void, void> >(c, result, ParameterPack<void, void, void, void>(), this->endTime - this->startTime));
		}
		template <class Cont>
		TesterResult<Cont, Result, ParameterPack<void, void, void, void> > impl(Cont& c, Result (Cont::*pm)() const)
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)();
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont, Result, ParameterPack<void, void, void, void> >(c, result, ParameterPack<void, void, void, void>(), this->endTime - this->startTime));
		}
		/**
		 * one parameter method
		 */
		template <class Cont, class Arg>
		TesterResult<Cont,
					 Result, ParameterPack<Arg, void, void, void> >
		impl(Cont& c, Result (Cont::*pm)(Arg), Arg arg)
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)(arg);
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont, Result, ParameterPack<Arg, void, void, void> >(c, result, ParameterPack<Arg, void, void, void>(arg), this->endTime - this->startTime));
		}
		template <class Cont, class Arg>
		TesterResult<Cont,
					 Result, ParameterPack<Arg, void, void, void> >
		impl(Cont& c, Result (Cont::*pm)(Arg) const, Arg arg)
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)(arg);
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont, Result, ParameterPack<Arg, void, void, void> >(c, result, ParameterPack<Arg, void, void, void>(arg), this->endTime - this->startTime));
		}
		/**
		 * two parameter method
		 */
		template <class Cont, class Arg1, class Arg2>
		TesterResult<Cont, Result, ParameterPack<Arg1, Arg2, void, void> > impl(Cont& c, Result (Cont::*pm)(Arg1, Arg2), Arg1 arg1, Arg2 arg2)
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)(arg1, arg2);
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont, Result, ParameterPack<Arg1, Arg2, void, void> >(c, result, ParameterPack<Arg1, Arg2, void, void>(arg1, arg2), this->endTime - this->startTime));
		}
		template <class Cont, class Arg1, class Arg2>
		TesterResult<Cont, Result, ParameterPack<Arg1, Arg2, void, void> > impl(Cont& c, Result (Cont::*pm)(Arg1, Arg2) const, Arg1 arg1, Arg2 arg2)
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)(arg1, arg2);
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont, Result, ParameterPack<Arg1, Arg2, void, void> >(c, result, ParameterPack<Arg1, Arg2, void, void>(arg1, arg2), this->endTime - this->startTime));
		}
		/**
		 * three parameter method
		 */
		template <class Cont, class Arg1, class Arg2, class Arg3>
		TesterResult<Cont, Result, ParameterPack<Arg1, Arg2, Arg3, void> > impl(Cont& c, Result (Cont::*pm)(Arg1, Arg2, Arg3), Arg1 arg1, Arg2 arg2, Arg3 arg3)
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)(arg1, arg2, arg3);
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont, Result, ParameterPack<Arg1, Arg2, Arg3, void> >(c, result, ParameterPack<Arg1, Arg2, Arg3, void>(arg1, arg2, arg3), this->endTime - this->startTime));
		}
		template <class Cont, class Arg1, class Arg2, class Arg3>
		TesterResult<Cont, Result, ParameterPack<Arg1, Arg2, Arg3, void> > impl(Cont& c, Result (Cont::*pm)(Arg1, Arg2, Arg3) const, Arg1 arg1, Arg2 arg2, Arg3 arg3)
		{
			this->startTime = std::chrono::steady_clock::now();
			Result result = (c.*pm)(arg1, arg2, arg3);
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont, Result, ParameterPack<Arg1, Arg2, Arg3, void> >(c, result, ParameterPack<Arg1, Arg2, Arg3, void>(arg1, arg2, arg3), this->endTime - this->startTime));
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
		TesterResult<Cont, void, ParameterPack<void, void, void, void> > impl(Cont& c, void (Cont::*pm)())
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)();
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont,
								 void,
								 ParameterPack<void, void, void, void> >(c, ParameterPack<void, void, void, void>(), this->endTime - this->startTime));
		}
		template <class Cont>
		TesterResult<Cont, void, ParameterPack<void, void, void, void> > impl(Cont& c, void (Cont::*pm)() const)
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)();
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont,
								 void,
								 ParameterPack<void, void, void, void> >(c, ParameterPack<void, void, void, void>(), this->endTime - this->startTime));
		}
		/**
		 * one parameter method
		 */
		template <class Cont, class Arg>
		TesterResult<Cont, void, ParameterPack<Arg, void, void, void> > impl(Cont& c, void (Cont::*pm)(Arg), Arg arg)
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)(arg);
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont,
								 void,
								 ParameterPack<Arg, void, void, void> >(c, ParameterPack<Arg, void, void, void>(arg), this->endTime - this->startTime));
		}
		template <class Cont, class Arg>
		TesterResult<Cont, void, ParameterPack<Arg, void, void, void> > impl(Cont& c, void (Cont::*pm)(Arg) const, Arg arg)
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)(arg);
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont,
								 void,
								 ParameterPack<Arg, void, void, void> >(c, ParameterPack<Arg, void, void, void>(arg), this->endTime - this->startTime));
		}
		/**
		 * two parameter method
		 */
		template <class Cont, class Arg1, class Arg2>
		TesterResult<Cont, void, ParameterPack<Arg1, Arg2, void, void> > impl(Cont& c, void (Cont::*pm)(Arg1, Arg2), Arg1 arg1, Arg2 arg2)
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)(arg1, arg2);
			this->endTime = std::chrono::steady_clock::now();
			return TesterResult<Cont,
								void,
								ParameterPack<Arg1, Arg2, void, void> >(c, ParameterPack<Arg1, Arg2, void, void>(arg1, arg2), this->endTime - this->startTime);
		}
		template <class Cont, class Arg1, class Arg2>
		TesterResult<Cont, void, ParameterPack<Arg1, Arg2, void, void> > impl(Cont& c, void (Cont::*pm)(Arg1, Arg2) const, Arg1 arg1, Arg2 arg2)
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)(arg1, arg2);
			this->endTime = std::chrono::steady_clock::now();
			return TesterResult<Cont,
								void,
								ParameterPack<Arg1, Arg2, void, void> >(c, ParameterPack<Arg1, Arg2, void, void>(arg1, arg2), this->endTime - this->startTime);
		}
		/**
		 * three parameter method
		 */
		template <class Cont, class Arg1, class Arg2, class Arg3>
		TesterResult<Cont, void, ParameterPack<Arg1, Arg2, Arg3, void> > impl(Cont& c, void (Cont::*pm)(Arg1, Arg2, Arg3), Arg1 arg1, Arg2 arg2, Arg3 arg3)
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)(arg1, arg2, arg3);
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont,
								 void,
								 ParameterPack<Arg1, Arg2, Arg3, void> >(c, ParameterPack<Arg1, Arg2, Arg3, void>(arg1, arg2, arg3), this->endTime - this->startTime));
		}
		template <class Cont, class Arg1, class Arg2, class Arg3>
		TesterResult<Cont, void, ParameterPack<Arg1, Arg2, Arg3, void> > impl(Cont& c, void (Cont::*pm)(Arg1, Arg2, Arg3) const, Arg1 arg1, Arg2 arg2, Arg3 arg3)
		{
			this->startTime = std::chrono::steady_clock::now();
			(c.*pm)(arg1, arg2, arg3);
			this->endTime = std::chrono::steady_clock::now();
			return (TesterResult<Cont,
								 void,
								 ParameterPack<Arg1, Arg2, Arg3, void> >(c, ParameterPack<Arg1, Arg2, Arg3, void>(arg1, arg2, arg3), this->endTime - this->startTime));
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
