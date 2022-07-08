#ifndef __FT_STACK_H__
#define __FT_STACK_H__

#include "vector.hpp"

namespace ft
{

	template <class T, class Container = ft::vector<T> >
	class stack
	{
	private:
		typedef T value_type;
		typedef Container container_type;
		typedef typename container_type::size_type size_type;

	private:
		container_type base_;

	public:
		explicit stack(const container_type& cntr = container_type())
			: base_(cntr) {}

		bool empty() const
		{
			return (base_.empty());
		}

		void pop()
		{
			return (base_.pop_back());
		}

		void push(const value_type& val)
		{
			return (base_.push_back(val));
		}

		size_type size() const
		{
			return (base_.size());
		}

		value_type& top()
		{
			return (base_.back());
		}
		const value_type& top() const
		{
			return (base_.back());
		}

		template <class U, class Cont>
		friend bool operator==(const stack<U, Cont>& lhs, const stack<U, Cont>& rhs);
		template <class U, class Cont>
		friend bool operator!=(const stack<U, Cont>& lhs, const stack<U, Cont>& rhs);
		template <class U, class Cont>
		friend bool operator<(const stack<U, Cont>& lhs, const stack<U, Cont>& rhs);
		template <class U, class Cont>
		friend bool operator<=(const stack<U, Cont>& lhs, const stack<U, Cont>& rhs);
		template <class U, class Cont>
		friend bool operator>(const stack<U, Cont>& lhs, const stack<U, Cont>& rhs);
		template <class U, class Cont>
		friend bool operator>=(const stack<U, Cont>& lhs, const stack<U, Cont>& rhs);
	};
	template <class U, class Cont>
	bool operator==(const stack<U, Cont>& lhs, const stack<U, Cont>& rhs)
	{
		return (lhs.base_ == rhs.base_);
	}
	template <class U, class Cont>
	bool operator!=(const stack<U, Cont>& lhs, const stack<U, Cont>& rhs)
	{
		return !(lhs == rhs);
	}
	template <class U, class Cont>
	bool operator<(const stack<U, Cont>& lhs, const stack<U, Cont>& rhs)
	{
		return (lhs.base_ < rhs.base_);
	}
	template <class U, class Cont>
	bool operator<=(const stack<U, Cont>& lhs, const stack<U, Cont>& rhs)
	{
		return !(rhs < lhs);
	}
	template <class U, class Cont>
	bool operator>(const stack<U, Cont>& lhs, const stack<U, Cont>& rhs)
	{
		return (rhs < lhs);
	}
	template <class U, class Cont>
	bool operator>=(const stack<U, Cont>& lhs, const stack<U, Cont>& rhs)
	{
		return !(lhs < rhs);
	}
}

#endif
