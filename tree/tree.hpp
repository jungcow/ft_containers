#ifndef __FT_BST_H__
#define __FT_BST_H__

#include <iostream>

#include "../type.hpp" //TODO: 지우기

namespace ft
{
	template <class Node>
	class Tree;
}

/**
 * @class
 *
 * @param Node: Node for Tree
 */
template <class Node>
class ft::Tree : public Node
{
public:
	typedef typename Node::value_type value_type;
	typedef typename Node::node_size_type node_size_type;

private:
	Node* root_;
	node_size_type size_;

public:
	Tree() : root_(NULL), size_(0)
	{
		root_ = createNode();
	}

	~Tree()
	{
		deleteAllNodes(root_);
	}

	bool empty() const
	{
		return size_ == 0;
	}

	node_size_type size() const
	{
		return size_;
	}

	Node* find(const value_type& value) const
	{
		return (find(root_->getLeft(), value));
	}

	Node* insert(const value_type& value)
	{
		Node* result = Node::insert(root_->getLeft(), value);
		if (!result)
			return NULL;
		size_++;
		root_->setLeft(result);
		root_->getLeft()->setColor(Node::Black);
		return (root_);
	}

	node_size_type erase(const value_type& value)
	{
		if (empty())
			return 0;

		if (!Node::erase(root_->getLeft(), value))
			return 0;
		size_--;
		return 1;
	}

	void printByInOrderTraversal() const
	{
		printByInOrderTraversal(root_->getLeft());
		std::cout << "\n";
	}

private:
	void printByInOrderTraversal(Node* node) const
	{
		if (node == NULL)
			return;
		printByInOrderTraversal(node->getLeft());
		std::cout << node->getValue().first << "(" << node->getRank() << ")" << '-';
		printByInOrderTraversal(node->getRight());
	}

	Node* createNode(const value_type& value = value_type())
	{
		return Node::createNode(value);
	}

	void deleteNode(Node* node)
	{
		Node::deleteNode(node);
	}

	void deleteAllNodes(Node* node)
	{
		Node::deleteAllNodes(node);
	}
};

#endif
