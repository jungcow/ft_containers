#ifndef __FT_BST_H__
#define __FT_BST_H__

#include <iostream>  // TODO: 지우기
#include <memory>    // TODO: 지우기 -> default argument로 적은 std 지우기

namespace ft
{
	namespace tree
	{
		template <class BaseNode, template <class> class BalanceType>
		class BST;
	}
}

/**
 * @class
 *
 * @param Node: BaseNode for balance Tree
 * @param BalanceType(template): tree balance type to inherit for balancing
 */
template <class BaseNode, template <class> class BalanceType>
class ft::tree::BST : BalanceType<BaseNode>
{
private:
	typedef typename BalanceType<BaseNode>::Node Node;
	typedef typename Node::value_type value_type;

public:
	typedef typename Node::node_allocator_type node_allocator_type;

	typedef typename Node::node_value_type node_value_type;
	typedef typename Node::node_pointer node_pointer;
	typedef typename Node::node_reference node_reference;
	typedef typename Node::node_const_pointer node_const_pointer;
	typedef typename Node::node_const_reference node_const_reference;

	typedef typename Node::node_size_type node_size_type;
	typedef typename Node::node_difference_type node_difference_type;

private:
	Node* root_;
	node_size_type size_;

public:
	BST() : BalanceType<BaseNode>(), root_(NULL), size_(0)
	{
		std::cout << "hello\n";
		root_ = this->createNode();
		std::cout << reinterpret_cast<void*>(root_) << std::endl;
		root_->setLeft(NULL);
		root_->setRight(NULL);
		std::cout << "BST Default Constructor\n";
	}

	~BST()
	{
		std::cout << "BST Default Destructor\n";
		// this->deleteAllNodes(root_->getLeft());
		// this->deleteNode(root_->getRight());
		// this->deleteNode(root_);
		this->deleteAllNodes(root_);
		std::cout << reinterpret_cast<void*>(root_) << std::endl;
		// this->deleteNode(root_);
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
		std::cout << reinterpret_cast<void*>(root_->getLeft()) << std::endl;
		Node* result = Node::insert(root_->getLeft(), value);
		std::cout << "result: " << reinterpret_cast<void*>(result) << std::endl;
		if (!result)
			return NULL;
		size_++;
		root_->setLeft(result);
		return (root_);
	}

	node_size_type erase(const value_type& value)
	{
		if (empty())
			return 0;

		if (!erase(root_->getLeft(), value))
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

private:
};

#endif
