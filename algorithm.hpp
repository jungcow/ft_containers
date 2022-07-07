#ifndef __FT_ALGORITHM_H__
#define __FT_ALGORITHM_H__

/**
 * lexicographical_compare
 * equal
 */

namespace ft
{
	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (*first1 != *first2)
				return false;
			first1++;
			first2++;
		}
		return true;
	}

	template <class InputIterator1, class Inputiterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1, Inputiterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return false;
			first1++;
			first2++;
		}
		return true;
	}

	/**
	 * lexicographically compare이 true다 -> range1이 range2보다 사전적으로 작다.
	 * false다 -> range1이 range2보다 사전적으로 같거나 크다.
	 *
	 * ※ 사전적으로 작다: 사전에서 더 앞쪽에(먼저) 나온다.
	 *
	 * example
	 * 1. Apple, AppleOrange -> true
	 * 2. Apple, Apple -> false (같이 때문)
	 * 3. Apple, App -> false (사전적으로 Apple이 App보다 크기 때문)
	 */
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2)
				return false;
			if (*first2 < *first1)
				return false;
			if (*first1 < *first2)
				return true;
			first1++;
			first2++;
		}
		return (first2 != last2);  // first2도 동시에 끝났으면 이 두 range는 같다
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2,
								 Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2)
				return false;
			if (comp(*first2, *first1))
				return false;
			if (comp(*first1, *first2))
				return true;
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

}

#endif
