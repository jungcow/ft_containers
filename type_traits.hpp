#ifndef _TYPE_TRAITS_H__
#define _TYPE_TRAITS_H__

#include <iostream>

namespace ft
{
	struct true_type { };
	struct false_type { };

	template <bool Cond, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if<true, T> {
	public:
		typedef T type;
	};


	template <class, class>
	struct is_convertible {
		enum { value = 0 };
		typedef false_type type;
	};

	template <class _Tp>
	struct is_convertible<_Tp, _Tp> {
		enum { value = 1 };
		typedef true_type type;
	};
	// is_integral
	// is_convertible
	// interal_constant ??

}

#endif