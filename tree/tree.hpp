#ifndef __FT_BST_H__
#define __FT_BST_H__

#include <iostream>

#include "../type.hpp"  //TODO: 지우기

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
	typedef typename Node::BalanceNode BalanceNode;

private:
	BalanceNode* root_;
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

	BalanceNode* find(const value_type& value) const
	{
		return (Node::find(root_->getLeft(), value));
	}

	BalanceNode* insert(const value_type& value)
	{
		BalanceNode* result = Node::insert(root_->getLeft(), value);
		if (!result)
			return NULL;
		size_++;
		root_->setLeft(result);
		// TODO: 색상에 관한건 too specific하다. 좀더 general한 접근이 필요.
		root_->getLeft()->setColor(BalanceNode::Black);
		return (root_);
	}

	node_size_type erase(const value_type& value)
	{
		std::cout << type(value) << std::endl;
		if (empty())
			return 0;

		BalanceNode* result = Node::erase(root_->getLeft(), value, root_);
		std::cout << "erase finished\n";
		if (!result)
			return 0;
		root_->setLeft(result);
		root_->getLeft()->setColor(BalanceNode::Black);
		size_--;
		return 1;
	}

	void printByInOrderTraversal() const
	{
		printByInOrderTraversal(root_->getLeft());
		std::cout << "\n";
	}

private:
	void printByInOrderTraversal(BalanceNode* node) const
	{
		if (node == NULL)
			return;
		printByInOrderTraversal(node->getLeft());

		std::cout << node->getValue().first << "(" << node->getRank() << ", ";
		// TODO: 색상에 관한건 too specific하다. 좀더 general한 접근이 필요.
		if (node->getColor() == BalanceNode::Red)
			std::cout << "R";
		else
			std::cout << "B";
		std::cout << ")" << '-';
		printByInOrderTraversal(node->getRight());
	}

	BalanceNode* createNode(const value_type& value = value_type())
	{
		return Node::createNode(value);
	}

	void deleteNode(BalanceNode* node)
	{
		Node::deleteNode(node);
	}

	void deleteAllNodes(BalanceNode* node)
	{
		Node::deleteAllNodes(node);
	}
};

#endif
