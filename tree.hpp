#ifndef __FT_TREE_H__
#define __FT_TREE_H__

#include <iostream>  // TODO: 지우기
#include <limits>
#include <memory>

#include "utility.hpp"

namespace ft
{
	namespace tree
	{
		template <class T>
		class Node;

		template <class T, class Comp, class Alloc>
		class BST;

		template <class T, class Comp, class Alloc>
		class RBTree;
	}
}

template <class T>
class ft::tree::Node
{
public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;

	typedef size_t size_type;

private:
	value_type val_;
	Node* left_;
	Node* right_;
	size_type rank_;

public:
	Node(const value_type& value) : val_(value), left_(NULL), right_(NULL), rank_(0) {}

	const_reference getValue(void) const
	{
		return (val_);
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
		val_ = value;
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

template <class T, class Comp, class Alloc = std::allocator<T> >
class ft::tree::BST
{
private:
	typedef ft::tree::Node<T> Node;

	typedef typename Node::size_type size_type;

	typedef typename Node::value_type value_type;
	typedef typename Node::pointer pointer;
	typedef typename Node::const_pointer const_pointer;
	typedef typename Node::reference reference;
	typedef typename Node::const_reference const_reference;

	typedef Alloc allocator_type;
	typedef typename allocator_type::template rebind<Node>::other node_allocator_type;

private:
	Node* root_;
	size_type size_;
	node_allocator_type allocator_;
	Comp compareValue;

public:
	BST(Comp compare, node_allocator_type alloc = node_allocator_type())
		: root_(NULL), size_(0), allocator_(alloc), compareValue(compare)
	{
	}

	/**
	 * TODO:
	 * 복사 생성자
	 * 대입 연산자?
	 */

	~BST()
	{
		deleteAllNodes(root_);
	}

public:
	bool empty() const
	{
		return size_ == 0;
	}

	size_type size() const
	{
		return size_;
	}

	Node* find(const value_type& value) const
	{
		return (find(root_, value));
	}

	Node* insert(const value_type& value)
	{
		Node* result = insert(root_, value);
		if (!result)
			return NULL;
		size_++;
		return (root_ = result);
	}

	size_type erase(const value_type& value)
	{
		if (empty())
			return 0;

		if (!erase(root_, value))
			return 0;
		size_--;
		return 1;
	}

	void printByInOrderTraversal() const
	{
		printByInOrderTraversal(root_);
		std::cout << "\n";
	}

private:
	void printByInOrderTraversal(Node* node) const
	{
		if (node == NULL)
			return;
		printByInOrderTraversal(node->getLeft());
		std::cout << node->getValue().first << '-';
		printByInOrderTraversal(node->getRight());
	}
	Node* find(Node* node, const value_type& value) const
	{
		if (node == NULL)
			return NULL;

		if (compareValue(node->getValue(), value))
			return find(node->getRight(), value);
		else if (compareValue(value, node->getValue()))
			return find(node->getLeft(), value);
		return node;
	}

	Node* insert(Node* node, const value_type& value)
	{
		if (node == NULL)
			return (createNode(value));

		if (compareValue(node->getValue(), value))
			node->setRight(insert(node->getRight(), value));
		else if (compareValue(value, node->getValue()))
			node->setLeft(insert(node->getLeft(), value));
		return node;
	}

	Node* erase(Node* node, const value_type& value)
	{
		if (node == NULL)
			return NULL;
		if (compareValue(node->getValue(), value))
			node->setRight(erase(node->getRight(), value));
		else if (compareValue(value, node->getValue()))
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

		return node;
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
			deleteNode(node);
			return NULL;
		}
		return eraseMinNodeFrom(node);
	}

private:
	Node* createNode(const value_type& value)
	{
		Node* newNode = allocator_.allocate(1);
		allocator_.construct(newNode, value);
		return newNode;
	}

	void deleteNode(Node* node)
	{
		allocator_.destroy(node);
		allocator_.deallocate(node, 1);
	}

	void deleteAllNodes(Node* node)
	{
		if (node == NULL)
			return;
		deleteAllNodes(node->getRight());
		deleteAllNodes(node->getLeft());
		allocator_.destroy(node);
		allocator_.deallocate(node, 1);
	}
};

#endif
