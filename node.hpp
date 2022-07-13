#ifndef __FT_NODE_H__
#define __FT_NODE_H__

#include "type_traits.hpp"

namespace ft
{
	namespace tree
	{
		template <class P1, class P2, class Alloc>
		class Node;

		template <class Iterator, class Pointer, class ValueIter, class ValuePointer>
		class node_iterator;
	}
}

template <class P1, class P2, class Alloc>
class ft::tree::Node
{
public:
	typedef Alloc allocator_type;

	typedef typename allocator_type::value_type value_type;
	typedef typename allocator_type::size_type size_type;

	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;

	typedef Node* node_pointer;
	typedef const Node* const_node_pointer;
	typedef node_iterator<node_pointer, node_pointer, P1, P2> iterator;
	typedef node_iterator<const_node_pointer, node_pointer, P1, P2> const_iterator;

private:
	pointer val_;
	Node* left_;
	Node* right_;
	size_type rank_;
	allocator_type allocator_;

public:
	Node(const value_type& value, const allocator_type& alloc = allocator_type())
		: val_(NULL), left_(NULL), right_(NULL), rank_(1), allocator_(alloc)
	{
		val_ = allocator_.allocate(1);
		allocator_.construct(val_, value);
	}

	template <class Pointer>
	Node(const Node<Pointer, ft::enable_if<
								 ft::is_same<Pointer, P2>::value,
								 P2>::type>& other,
		 const allocator_type& alloc = allocator_type())
		: val_(NULL), left_(other.left_), right_(other.right_), rank_(other.rank_), allocator_(alloc)
	{
		val_ = allocator_.allocate(1);
		allocator_.construct(val_, *other.val_);
	}

	Node& operator=(const Node& other)
	{
		// TODO: trivial_destructible 확인해서 최적화 하기
		allocator_.destroy(val_);
		allocator_.construct(val_, *other.val_);
		left_ = other.left_;
		right_ = other.right_;
		rank_ = other.rank_;
		return (*this);
	}

	reference operator*() const
	{
		return (*val);
	}

	const_reference getValue(void) const
	{
		return (*val_);
	}
	Node* getLeft(void) const
	{
		return (left_);
	}
	Node* getRight(void) const
	{
		return (right_);
	}
	size_type getRank(void) const
	{
		return (rank_);
	}

	void setValue(const_reference value)
	{
		*val_ = value;
	}
	void setLeft(Node* node)
	{
		left_ = node;
	}
	void setRight(Node* node)
	{
		right_ = node;
	}
	void setRank(size_type r)
	{
		rank_ = r;
	}
};

template <class Iterator, class Pointer, class ValueIter, class ValuePointer>
class node_iterator
{
public:
	typedef ft::iterator<std::bidirectional_iterator_tag, ft::remove_pointer<Iterator>::type> iterator;
	// typedef ft::iterator<std::bidirectional_iterator_tag, ft::remove_pointer<ValueIter>::type> value_iterator;

	typedef typename iterator::value_type value_type;
	typedef typename iterator::pointer pointer;
	typedef typename iterator::reference reference;
	typedef typename iterator::difference_type difference_type;
	typedef typename iterator::iterator_category iterator_category;

	typedef typename ft::remove_pointer<ValueIter>::type inner_value_type;
	typedef inner_value_type* inner_pointer;
	typedef inner_value_type& inner_reference;
	typedef const inner_value_type* const_inner_pointer;
	typedef const inner_value_type& const_inner_reference;

private:
	Iterator base_;

public:
	node_iterator() {}

	template <class P, class Vp>
	node_iterator(const node_iterator<
				  P, typename ft::enable_if<ft::is_same<P, Pointer>::value, Pointer>::type,
				  Vp, typename ft::enable_if<ft::is_same<Vp, ValuePointer>::value, ValuePointer>::type>& other)
		: base_(node_iterator.base())
	{
	}

	explicit node_iterator(const Iterator& otherNode)
		: base_(otherNode)
	{
	}

	node_iterator& operator=(const node_iterator& other)
	{
		base_ = other.base_;
		return (*this);
	}

	~node_iterator() {}

	Iterator base(void)
	{
		return base_;
	}

	inner_reference operator*() const
	{
		return (*base_);
	}

	template <class I, class P, class V, class Vp>
	friend bool operator==(const node_iterator<I, P, V, Vp>& lhs, const node_iterator<I, P, V, Vp>& rhs);
	template <class I, class P, class V, class Vp>
	friend bool operator!=(const node_iterator<I, P, V, Vp>& lhs, const node_iterator<I, P, V, Vp>& rhs);
	template <class I, class P, class V, class Vp>
	friend bool operator<(const node_iterator<I, P, V, Vp>& lhs, const node_iterator<I, P, V, Vp>& rhs);
	template <class I, class P, class V, class Vp>
	friend bool operator<=(const node_iterator<I, P, V, Vp>& lhs, const node_iterator<I, P, V, Vp>& rhs);
	template <class I, class P, class V, class Vp>
	friend bool operator>(const node_iterator<I, P, V, Vp>& lhs, const node_iterator<I, P, V, Vp>& rhs);
	template <class I, class P, class V, class Vp>
	friend bool operator>=(const node_iterator<I, P, V, Vp>& lhs, const node_iterator<I, P, V, Vp>& rhs);
};

namespace ft
{
	namespace tree
	{
		template <class I, class P, class V, class Vp>
		bool operator==(const node_iterator<I, P, V, Vp>& lhs, const node_iterator<I, P, V, Vp>& rhs)
		{
			return (lhs.base_ == rhs.base_);
		}
		template <class I, class P, class V, class Vp>
		bool operator!=(const node_iterator<I, P, V, Vp>& lhs, const node_iterator<I, P, V, Vp>& rhs)
		{
			return !(lhs == rhs);
		}
		template <class I, class P, class V, class Vp>
		bool operator<(const node_iterator<I, P, V, Vp>& lhs, const node_iterator<I, P, V, Vp>& rhs)
		{
			return (lhs.base_ < rhs.base_);
		}
		template <class I, class P, class V, class Vp>
		bool operator<=(const node_iterator<I, P, V, Vp>& lhs, const node_iterator<I, P, V, Vp>& rhs)
		{
			return !(rhs < lhs);
		}
		template <class I, class P, class V, class Vp>
		bool operator>(const node_iterator<I, P, V, Vp>& lhs, const node_iterator<I, P, V, Vp>& rhs)
		{
			return (rhs < lhs);
		}
		template <class I, class P, class V, class Vp>
		bool operator>=(const node_iterator<I, P, V, Vp>& lhs, const node_iterator<I, P, V, Vp>& rhs)
		{
			return !(lhs < rhs);
		}
	}
}

#endif
