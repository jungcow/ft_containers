#ifndef _TYPE_TRAITS_H__
#define _TYPE_TRAITS_H__

#include <iostream>

namespace ft
{
	struct true_type {};
	struct false_type {};

	template <bool, class T = void>
	struct enable_if {};

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
	// is_integral
	// is_convertible
	// interal_constant ??

}

#endif