#ifndef __FT_UTILITY_H__
#define __FT_UTILITY_H__

#include "type_traits.hpp"  // check_type

/**
 * make_pair
 * pair
 * is_pair
 */

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair() : first(), second() {}

		template <class U, class V>
		pair(const pair<U, V>& pr) : first(pr.first), second(pr.second)
		{
		}

		pair(const first_type& a, const second_type& b) : first(a), second(b) {}

		pair& operator=(const pair& pr)
		{
			first = pr.first;
			second = pr.second;
		}

		template <class U1, class U2>
		friend bool operator==(const pair<U1, U2>& lhs, const pair<U1, U2>& rhs);
		template <class U1, class U2>
		friend bool operator!=(const pair<U1, U2>& lhs, const pair<U1, U2>& rhs);
		template <class U1, class U2>
		friend bool operator<(const pair<U1, U2>& lhs, const pair<U1, U2>& rhs);
		template <class U1, class U2>
		friend bool operator<=(const pair<U1, U2>& lhs, const pair<U1, U2>& rhs);
		template <class U1, class U2>
		friend bool operator>(const pair<U1, U2>& lhs, const pair<U1, U2>& rhs);
		template <class U1, class U2>
		friend bool operator>=(const pair<U1, U2>& lhs, const pair<U1, U2>& rhs);
	};

	template <class T1, class T2>
	bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}
	template <class T1, class T2>
	bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (!(lhs == rhs));
	}
	template <class T1, class T2>
	bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		// like lexicographical compare
		if (lhs.first < rhs.first)
			return true;
		if (!(rhs.first < lhs.first) && lhs.second < rhs.second)
			return true;
		return false;
	}
	template <class T1, class T2>
	bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(rhs < lhs);
	}
	template <class T1, class T2>
	bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (rhs < lhs);
	}
	template <class T1, class T2>
	bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return pair<T1, T2>(x, y);
	}

	template <class T>
	struct is_pair
	{
	private:
		struct two
		{
			char c[2];
		};

		template <class U>
		static two test(...);

		template <class U>
		static char test(typename ft::check_type<typename U::first_type>::type* = 0,
						 typename ft::check_type<typename U::second_type>::type* = 0);

	public:
		static const bool value = (sizeof(test<T>(0, 0)) == 1);
	};
}

#endif
