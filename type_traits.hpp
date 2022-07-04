#ifndef __FT_TYPE_TRAITS_H__
#define __FT_TYPE_TRAITS_H__

/**
 * is_integral
 * enable_if
 */

#include <cstdint>

namespace ft
{
	/**
	 * enable_if
	 */
	template <bool Cond, typename T = void>
	struct enable_if
	{
	};

	template <typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	/**
	 * is_integral
	 */
	template <typename T>
	struct is_integral
	{
		static const bool value = false;
	};

	template <>
	struct is_integral<bool>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<char>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<char16_t>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<char32_t>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<wchar_t>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<signed char>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<short int>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<int>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<long int>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<long long int>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<unsigned char>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<unsigned short int>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<unsigned int>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<unsigned long int>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<unsigned long long int>
	{
		static const bool value = true;
	};

	/**
	 * is_same
	 */
	template <typename T, typename U>
	struct is_same
	{
		static const bool value = false;
	};

	template <typename T>
	struct is_same<T, T>
	{
		static const bool value = true;
	};
}

#endif