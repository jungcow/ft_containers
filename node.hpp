#ifndef __FT_NODE_H__
#define __FT_NODE_H__

#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft
{
	namespace tree
	{
		template <class P1, class P2, class Alloc>
		class Node;

		template <class Iterator, class ValueIter, class ValuePointer>
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

private:
	typedef Node* node_pointer;
	typedef const Node* const_node_pointer;

public:
	typedef node_iterator<node_pointer, P1, P2> iterator;
	typedef node_iterator<const_node_pointer, P1, P2> const_iterator;

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
	Node(const Node<Pointer, typename ft::enable_if<ft::is_same<Pointer, P2>::value, P2>::type, Alloc>& other,
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

	reference getValue(void) const
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

template <class Iterator, class ValueIter, class ValuePointer>
class ft::tree::node_iterator
{
private:
	typedef ft::iterator<std::bidirectional_iterator_tag, typename ft::remove_pointer<Iterator>::type> iterator;

public:
	typedef typename ft::remove_pointer<ValueIter>::type inner_value_type;
	typedef inner_value_type* inner_pointer;
	typedef inner_value_type& inner_reference;
	typedef const inner_value_type* const_inner_pointer;
	typedef const inner_value_type& const_inner_reference;

public:
	typedef typename iterator::value_type value_type;
	typedef typename iterator::pointer pointer;
	typedef typename iterator::reference reference;
	typedef typename iterator::difference_type difference_type;
	typedef typename iterator::iterator_category iterator_category;

private:
	Iterator base_;

public:
	node_iterator()
	{
		std::cout << "node iterator default constructor\n";
	}

	template <class P, class Vp>
	node_iterator(const node_iterator<P, Vp,
									  typename ft::enable_if<ft::is_same<Vp, ValuePointer>::value, ValuePointer>::type>& other)
		: base_(reinterpret_cast<Iterator>(other.base()))
	{
		std::cout << "node iterator copy constructor\n";
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

	Iterator base(void) const
	{
		return base_;
	}

	inner_reference operator*() const
	{
		return (base_->getValue());
	}

	inner_pointer operator->() const
	{
		return &(base_->getValue());
	}

	template <class I, class V, class Vp>
	friend bool operator==(const node_iterator<I, V, Vp>& lhs, const node_iterator<I, V, Vp>& rhs);
	template <class I, class V, class Vp>
	friend bool operator!=(const node_iterator<I, V, Vp>& lhs, const node_iterator<I, V, Vp>& rhs);
};

namespace ft
{
	namespace tree
	{
		template <class I, class V, class Vp>
		bool operator==(const node_iterator<I, V, Vp>& lhs, const node_iterator<I, V, Vp>& rhs)
		{
			return (lhs.base_ == rhs.base_);
		}
		template <class I, class V, class Vp>
		bool operator!=(const node_iterator<I, V, Vp>& lhs, const node_iterator<I, V, Vp>& rhs)
		{
			return !(lhs == rhs);
		}
	}
}

#endif
