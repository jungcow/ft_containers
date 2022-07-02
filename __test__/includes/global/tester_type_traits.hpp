#ifndef __TESTER_TYPE_TRAITS_H__
#define __TESTER_TYPE_TRAITS_H__

#include "global/parameter_pack.hpp"

namespace ContainerAssured
{

	template <typename T>
	struct is_lt_one
	{
		static const bool value = (T::num < 1);
	};

	template <typename T>
	struct is_lt_two
	{
		static const bool value = (T::num < 2);
	};
	template <typename T>
	struct is_lt_three
	{
		static const bool value = (T::num < 3);
	};
	template <typename T>
	struct is_lt_four
	{
		static const bool value = (T::num < 4);
	};

	typedef ParameterPack<void, void, void, void> voidParameterPack;

	template <class Arg1>
	struct OneParameterPack
	{
		typedef ParameterPack<Arg1, void, void, void> type;
	};

	template <class Arg1, class Arg2>
	struct TwoParameterPack
	{
		typedef ParameterPack<Arg1, Arg2, void, void> type;
	};

	template <class Arg1, class Arg2, class Arg3>
	struct ThreeParameterPack
	{
		typedef ParameterPack<Arg1, Arg2, Arg3, void> type;
	};
}

#endif