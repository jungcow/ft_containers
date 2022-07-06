#ifndef __FT_ITERATOR_H__
#define __FT_ITERATOR_H__

#include <cstddef>  // ptrdiff_t

#include "type_traits.hpp"  // input_iterator_tag

namespace ft
{
	/**
	 * iterator_tag class
	 *
	 * iterator가 어떤 iterator인지를 단지 판별하는 용도로 내부는
	 * 비어있다.
	 */
	struct input_iterator_tag
	{
	};
	struct output_iterator_tag
	{
	};
	struct forward_iterator_tag : ft::input_iterator_tag
	{
	};
	struct bidirectional_iterator_tag : ft::forward_iterator_tag
	{
	};
	struct random_access_iterator_tag : ft::bidirectional_iterator_tag
	{
	};

	/**
	 * iterator class
	 *
	 * iterator에 필요한 type들이 있는 기본이 되는 틀을 제공하는 용도로써,
	 * 실제 container에서 사용될 container에서 구체적인 iterator를 정의할 때,
	 * 상속과 같은 방식으로 있어야 할 type들을 전부 가져올 수 있다.
	 */
	template <class Category,
			  class T,
			  class Distance = ptrdiff_t,
			  class Pointer = T*,
			  class Reference = T&>
	struct iterator
	{
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

	/**
	 * iterator_traits 클래스
	 *
	 * iterator 클래스와 매우 비슷해보이나, 만약 pointer가 iterator 템플릿
	 * 인자로 들어올 경우, iterator 클래스가 가지고 있는 여러 member type에
	 * 접근하듯이 접근하게 되면 pointer에는 해당 member type이 정의되어 있지
	 * 않으므로 에러가 발생하게 된다. 이를 방지하기 위해 iterator_traits는
	 * pointer에 대한 특수화를 하여 pointer일 때 어떠한 member type을 가질지를
	 * 정의해놓았다.
	 */
	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};
	template <class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
	};
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template <class T>
	struct iterator_traits_wrapper
	{
		typedef typename iterator_traits<T>::iterator_category iterator_category;
	};

	template <>
	struct iterator_traits_wrapper<int>
	{
		typedef char iterator_category;
	};
	template <>
	struct iterator_traits_wrapper<ft::input_iterator_tag>
	{
		typedef ft::input_iterator_tag iterator_category;
	};

	/**
	 * reverse_iterator class
	 *
	 * iterator를 template 인자로 받아서 reverse로 동작하게끔 하는
	 * class template
	 */
	template <class Iterator>
	class reverse_iterator : public ft::iterator<typename ft::iterator_traits<Iterator>::iterator_category,
												 typename ft::iterator_traits<Iterator>::value_type,
												 typename ft::iterator_traits<Iterator>::difference_type,
												 typename ft::iterator_traits<Iterator>::pointer,
												 typename ft::iterator_traits<Iterator>::reference>
	{
	private:
		typedef Iterator iterator_type;
		iterator_type base_;

	public:
		reverse_iterator() : base_() {}

		explicit reverse_iterator(iterator_type it) : base_(it) {}

		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter>& rev_it) : base_(rev_it.base())
		{
		}

		iterator_type base() const
		{
			return base_;
		}
		/**
		 *
		 * Internally, the function decreases a copy of its base iterator
		 * and returns the result of dereferencing it.
		 */
		typename reverse_iterator::reference operator*() const
		{
			return *(base_ - 1);
		}

		reverse_iterator operator+(typename reverse_iterator::difference_type n) const
		{
			return (reverse_iterator(base_ - n));
		}

		reverse_iterator& operator++()
		{
			--base_;
			return (*this);
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator temp = *this;
			++(*this);
			return (temp);
		}

		reverse_iterator& operator+=(typename reverse_iterator::difference_type n)
		{
			base_ -= n;
			return (*this);
		}

		reverse_iterator operator-(typename reverse_iterator::difference_type n) const
		{
			return (reverse_iterator(base_ + n));
		}

		reverse_iterator& operator--()
		{
			++base_;
			return (*this);
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator temp = *this;
			--(*this);
			return (temp);
		}
		reverse_iterator& operator-=(typename reverse_iterator::difference_type n)
		{
			base_ += n;
			return (*this);
		}

		/**
		 * operator*를 호출하고 이 address를 반환한다고 한다.
		 * 참고: https://m.cplusplus.com/reference/iterator/reverse_iterator/operator-%3E/
		 */
		typename reverse_iterator::pointer operator->() const
		{
			return (&(operator*()));
		}

		template <class Iter>
		reverse_iterator& operator=(const reverse_iterator<Iter>& rev_it)
		{
			base_ = rev_it.base();
			return (*this);
		}

		typename reverse_iterator::reference operator[](typename reverse_iterator::difference_type n) const
		{
			return *(base_ + (-n - 1));
		}

	public:
		template <class Iter>
		friend bool operator==(const reverse_iterator<Iter>& lhs,
							   const reverse_iterator<Iter>& rhs);
		template <class Iter>
		friend bool operator!=(const reverse_iterator<Iter>& lhs,
							   const reverse_iterator<Iter>& rhs);
		template <class Iter>
		friend bool operator<(const reverse_iterator<Iter>& lhs,
							  const reverse_iterator<Iter>& rhs);
		template <class Iter>
		friend bool operator<=(const reverse_iterator<Iter>& lhs,
							   const reverse_iterator<Iter>& rhs);
		template <class Iter>
		friend bool operator>(const reverse_iterator<Iter>& lhs,
							  const reverse_iterator<Iter>& rhs);
		template <class Iter>
		friend bool operator>=(const reverse_iterator<Iter>& lhs,
							   const reverse_iterator<Iter>& rhs);
		template <class Iter>
		friend reverse_iterator<Iter> operator+(
			typename reverse_iterator<Iter>::difference_type n,
			const reverse_iterator<Iter>& rev_it);
		template <class Iter>
		friend typename reverse_iterator<Iter>::difference_type operator-(
			const reverse_iterator<Iter>& lhs,
			const reverse_iterator<Iter>& rhs);
	};

	template <class Iter>
	bool operator==(const reverse_iterator<Iter>& lhs,
					const reverse_iterator<Iter>& rhs)
	{
		return (lhs.base_ == rhs.base_);
	}
	template <class Iter>
	bool operator!=(const reverse_iterator<Iter>& lhs,
					const reverse_iterator<Iter>& rhs)
	{
		return (lhs.base_ != rhs.base_);
	}
	template <class Iter>
	bool operator<(const reverse_iterator<Iter>& lhs,
				   const reverse_iterator<Iter>& rhs)
	{
		return (lhs.base_ > rhs.base_);
	}
	template <class Iter>
	bool operator<=(const reverse_iterator<Iter>& lhs,
					const reverse_iterator<Iter>& rhs)
	{
		return (lhs.base_ >= rhs.base_);
	}
	template <class Iter>
	bool operator>(const reverse_iterator<Iter>& lhs,
				   const reverse_iterator<Iter>& rhs)
	{
		return (lhs.base_ < rhs.base_);
	}
	template <class Iter>
	bool operator>=(const reverse_iterator<Iter>& lhs,
					const reverse_iterator<Iter>& rhs)
	{
		return (lhs.base_ <= rhs.base_);
	}
	template <class Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n,
									 const reverse_iterator<Iter>& rev_it)
	{
		return (rev_it + n);
	}
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs,
																   const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base_ - lhs.base_);
	}
};

#endif
