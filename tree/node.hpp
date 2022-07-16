#ifndef __FT_NODE_H__
#define __FT_NODE_H__

#include "../iterator.hpp"
#include "../type_traits.hpp"

namespace ft
{
	namespace tree
	{
		template <class P1, class P2, class Compare, class Alloc>
		class Node;

		template <class Iterator, class ValueIter, class ValuePointer>
		class node_iterator;
	}
}

template <class P1, class P2, class Compare, class Alloc>
class ft::tree::Node
{
public:
	typedef Compare compare_type;
	typedef Alloc allocator_type;

	typedef typename allocator_type::value_type value_type;
	typedef typename allocator_type::size_type size_type;

	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;

protected:
	typedef typename allocator_type::template rebind<Node>::other node_allocator_type;

	typedef typename node_allocator_type::value_type node_value_type;
	typedef typename node_allocator_type::pointer node_pointer;
	typedef typename node_allocator_type::reference node_reference;
	typedef typename node_allocator_type::const_pointer node_const_pointer;
	typedef typename node_allocator_type::const_reference node_const_reference;

	typedef typename node_allocator_type::size_type node_size_type;
	typedef typename node_allocator_type::difference_type node_difference_type;

public:
	typedef node_iterator<Node*, P1, P2> iterator;
	typedef node_iterator<const Node*, P1, P2> const_iterator;

private:
	pointer val_;
	Node* left_;
	Node* right_;
	size_type rank_;
	allocator_type allocator_;
	node_allocator_type node_allocator_;
	compare_type compare_value_;

public:
	Node(const value_type& value, const compare_type& comp = compare_type(), const allocator_type& alloc = allocator_type())
		: val_(NULL),
		  left_(NULL),
		  right_(NULL),
		  rank_(1),
		  compare_value_(comp),
		  allocator_(alloc),
		  node_allocator_(node_allocator_type())
	{
		val_ = allocator_.allocate(1);
		allocator_.construct(val_, value);
	}

	template <class Pointer>
	Node(const Node<Pointer, typename ft::enable_if<ft::is_same<Pointer, P2>::value, P2>::type, Compare, Alloc>& other,
		 const compare_type& comp = compare_type(), const allocator_type& alloc = allocator_type())
		: val_(NULL),
		  left_(other.left_),
		  right_(other.right_),
		  rank_(other.rank_),
		  compare_value_(comp),
		  allocator_(alloc),
		  node_allocator_(node_allocator_type())
	{
		val_ = allocator_.allocate(1);
		allocator_.construct(val_, *other.val_);
	}

	~Node()
	{
		allocator_.destroy(val_);
		allocator_.deallocate(val_, 1);
	}

	Node& operator=(const Node& other)
	{
		// TODO: assign operator가 필요한지 확인하기
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

	Node* find(Node* node, const value_type& value) const
	{
		if (node == NULL)
			return NULL;

		if (node->getValue() < value)
			return find(node->getRight(), value);
		else if (value < node->getValue())
			return find(node->getLeft(), value);
		return node;
	}

	Node* insert(Node* node, const value_type& value)
	{
		if (node == NULL)
			return (createNode(value));

		if (node->getValue() < value)
			node->setRight(insert(node->getRight(), value));
		else if (value < node->getValue())
			node->setLeft(insert(node->getLeft(), value));
		node->setRank(calculateNodeRank(node));
		return node;
	}

	Node* erase(Node* node, const value_type& value)
	{
		if (node == NULL)
			return NULL;

		if (node->getValue() < value)
			node->setRight(erase(node->getRight(), value));
		else if (value < node->getValue())
			node->setLeft(erase(node->getLeft(), value));
		else
		{
			Node* tmp;
			if (node->getLeft() == NULL)
			{
				tmp = node->getRight();
				deleteNode(node);
				return tmp;
			}
			else if (node->getRight() == NULL)
			{
				tmp = node->getLeft();
				deleteNode(node);
				return tmp;
			}
			tmp = node;
			node = getMinNodeFrom(node->getRight());
			node->setRight(eraseMinNodeFrom(tmp->getRight()));
			node->setLeft(tmp->getLeft());
			deleteNode(tmp);
		}
		node->setRank(calculateNodeRank(node));
		return node;
	}

protected:
	bool operator<(const value_type& lhs, const value_type& rhs) const
	{
		return compare_value_(lhs, rhs);
	}

	Node* createNode(const value_type& value = value_type())
	{
		Node* newNode = node_allocator_.allocate(1);
		node_allocator_.construct(newNode, node_value_type(value));
		return newNode;
	}

	void deleteNode(Node* node)
	{
		node_allocator_.destroy(node);
		node_allocator_.deallocate(node, 1);
	}

	Node* getMinNodeFrom(Node* node)
	{
		if (node->getLeft() == NULL)
			return node;
		return (getMinNodeFrom(node->getLeft()));
	}

	Node* eraseMinNodeFrom(Node* node)
	{
		if (node->getLeft() == NULL)
		{
			Node* tmp = node->getRight();
			return tmp;
		}
		node->setLeft(eraseMinNodeFrom(node->getLeft()));
		node->setRank(calculateNodeRank(node));
		return node;
	}

	size_type calculateNodeRank(Node* node)
	{
		size_type lRank = 0;
		size_type rRank = 0;
		if (node->getLeft())
			lRank = node->getLeft()->getRank();
		if (node->getRight())
			rRank = node->getRight()->getRank();
		return (lRank + rRank + 1);
	}

	Node* calculateAllNodesRank(Node* node)
	{
		if (!node->getLeft() && !node->getRight())
		{
			node->setRank(1);
			return node;
		}

		size_type lRank = 0;
		size_type rRank = 0;

		if (node->getLeft())
			lRank = calculateAllNodesRank(node->getLeft())->getRank();
		if (node->getRight())
			rRank = calculateAllNodesRank(node->getRight())->getRank();
		node->setRank(lRank + rRank + 1);
		return (node);
	}
};

template <class Iterator, class ValueIter, class ValuePointer>
class ft::tree::node_iterator
{
private:
	typedef ft::iterator<std::bidirectional_iterator_tag, typename ft::remove_pointer<Iterator>::type> iterator;

public:
	// for value type
	typedef typename ft::remove_pointer<ValueIter>::type inner_value_type;
	typedef inner_value_type* inner_pointer;
	typedef inner_value_type& inner_reference;
	typedef const inner_value_type* const_inner_pointer;
	typedef const inner_value_type& const_inner_reference;

	// for node type
	typedef typename iterator::value_type value_type;
	typedef typename iterator::pointer pointer;
	typedef typename iterator::reference reference;
	typedef typename iterator::difference_type difference_type;
	typedef typename iterator::iterator_category iterator_category;

private:
	Iterator base_;  // same with Node*

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
