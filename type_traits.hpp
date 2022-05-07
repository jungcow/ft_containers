#ifndef _TYPE_TRAITS_H__
#define _TYPE_TRAITS_H__

#include <iostream>

#include "iterator.hpp"

namespace ft
{
	struct input_iterator_tag;
	struct true_type {
	};
	struct false_type {
	};

	template <bool, class T = void>
	struct enable_if {
	};

	template <class T>
	struct enable_if<true, T> {
	public:
		typedef T type;
	};

	template <typename, typename>
	struct is_same {
		enum { value = 0 };
		typedef false_type type;
	};
	template <typename T>
	struct is_same<T, T> {
		enum { value = 1 };
		typedef true_type type;
	};

	template <typename T>
	struct is_integral {
		enum { value = 0 };
		typedef false_type type;
	};

	template <>
	struct is_integral<bool> {
		enum { value = 1 };
		typedef true_type type;
	};
	template <>
	struct is_integral<char> {
		enum { value = 1 };
		typedef true_type type;
	};
	template <>
	struct is_integral<char16_t> {
		enum { value = 1 };
		typedef true_type type;
	};
	template <>
	struct is_integral<char32_t> {
		enum { value = 1 };
		typedef true_type type;
	};
	template <>
	struct is_integral<wchar_t> {
		enum { value = 1 };
		typedef true_type type;
	};
	template <>
	struct is_integral<signed char> {
		enum { value = 1 };
		typedef true_type type;
	};
	template <>
	struct is_integral<short int> {
		enum { value = 1 };
		typedef true_type type;
	};
	template <>
	struct is_integral<int> {
		enum { value = 1 };
		typedef true_type type;
	};
	template <>
	struct is_integral<long int> {
		enum { value = 1 };
		typedef true_type type;
	};
	template <>
	struct is_integral<long long int> {
		enum { value = 1 };
		typedef true_type type;
	};
	template <>
	struct is_integral<unsigned char> {
		enum { value = 1 };
		typedef true_type type;
	};
	template <>
	struct is_integral<unsigned short int> {
		enum { value = 1 };
		typedef true_type type;
	};
	template <>
	struct is_integral<unsigned int> {
		enum { value = 1 };
		typedef true_type type;
	};
	template <>
	struct is_integral<unsigned long int> {
		enum { value = 1 };
		typedef true_type type;
	};
	template <>
	struct is_integral<unsigned long long int> {
		enum { value = 1 };
		typedef true_type type;
	};
}

#endif