#ifndef __FT_RED_BLACK_BALANCE_H__
#define __FT_RED_BLACK_BALANCE_H__

namespace ft
{
	namespace tree
	{
		template <class BaseNode>
		class RedBlackBalance;
	}
}
template <class BaseNode>
class ft::tree::RedBlackBalance : public BaseNode
{
protected:
	enum Color
	{
		Red,
		Black
	};

	typedef RedBlackBalance<BaseNode> Node;

	typedef typename BaseNode::node_allocator_type node_allocator_type;
	typedef typename BaseNode::value_type value_type;
	typedef typename BaseNode::compare_type compare_type;

	typedef typename node_allocator_type::template rebind<RedBlackBalance>::other rb_node_allocator_type;
	typedef typename rb_node_allocator_type::node_value_type rb_node_value_type;
	typedef typename rb_node_allocator_type::node_pointer rb_node_pointer;
	typedef typename rb_node_allocator_type::node_reference rb_node_reference;
	typedef typename rb_node_allocator_type::node_const_pointer rb_node_const_pointer;
	typedef typename rb_node_allocator_type::node_const_reference rb_node_const_reference;

	typedef typename rb_node_allocator_type::node_size_type rb_node_size_type;
	typedef typename rb_node_allocator_type::node_difference_type rb_node_difference_type;

private:
	Color color_;
	rb_node_allocator_type rb_node_allocator_;

protected:
	RedBlackBalance(const value_type& value, const Color& color = RED)
		: BaseNode(value), color_(color), rb_node_allocator_(rb_node_allocator_type())
	{
	}

	template <class N>
	RedBlackBalance(cosnt RedBlackBalance<N>& other)
		: BaseNode(other), color_(other.getColor()), rb_node_allocator_(rb_node_allocator_type())
	{
	}

	Color& getColor(void) const
	{
		return (color_);
	}

	void setColor(const Color& color)
	{
		color_ = color;
	}

	void flipColor(Node* node)
	{
		node->setColor(!node->getColor());
	}

	void splitNode(Node* node)
	{
		if (node->getLeft())
			flipColor(node->getLeft());
		if (node->getRight())
			flipColor(node->getRight());
		flipColor(node);
	}

	bool isRed(Node* node) const
	{
		if (node == NULL)
			return false;
		return (node->getColor() == Red);
	}

	Node* rotateLeft(Node* node)
	{
		Node* tmp = node->getRight();
		tmp->setLeft(node);
		tmp->setRank(node->getRank());
		tmp->setColor(node->getColor());
		node->setRight(tmp->getLeft());
		node->setRank(this->calculateNodeRank(node));
		node->setColor(Red);
		return tmp;
	}

	Node* rotateRight(Node* node)
	{
		Node* tmp = node->getLeft();
		tmp->setRight(node);
		tmp->setRank(node->getRank());
		tmp->setColor(node->getColor());
		node->setLeft(tmp->getRight());
		node->setRank(this->calculateNodeRank(node));
		node->setColor(RED);
		return tmp;
	}

	Node* insert(Node* node, const value_type& value)
	{
		if (node == NULL)
			return (createNode(value));

		if (isRed(node->getLeft()) && isRed(node->getRight()))
			splitNode(node);
		if (node->getValue() < value)
			node->setRight(insert(node->getRight(), value));
		else if (value < node->getValue())
			node->setLeft(insert(node->getLeft(), value));
		node->setRank(calculateNodeRank(node));
		return balance(node);
	}

	Node* erase(Node* node, const value_type& value, Node** parent)
	{
		if (node == NULL)
			return NULL;

		if (node->getValue() < value)
			node->setRight(erase(node->getRight(), value, &node));
		else if (value < node->getValue())
			node->setLeft(erase(node->getLeft(), value, &node));
		else
		{
			if (isLeafNode(node))
			{
				if (!isRed(node))
				{
					Node* sibling = (*parent)->getRight();  // TODO:  sibling이 NULL인 경우는 없다고 생각했는데 다시 확인해보기
					if (isRed(sibling->getLeft()) || isRed(sibling->getRight()))
						return MoveNode(node, parent);
					return UnionNode(node, parent);
				}
				deleteNode(node);
				return NULL;
			}
			// 중위 후속자가 마땅치 않을 경우
			if (!node->getRight())
			{
				if (isRed(node))
				{
					Node* tmp = node->getLeft();
					deleteNode(node);
					return tmp;
				}
				// TODO: 오른쪽 자식이 null인 node가 black일 경우, 왼쪽 자식은 무조건 red -> 이거 확인해보기
				swapValue(node, node->getLeft());
				deleteNode(node->getLeft());
				node->setLeft(NULL);
			}
			else
			{
				swapValue(node, getMinNodeFrom(node->getRight()));
				node->setRight(erase(node->getRight(), value, &node));
			}
		}
		node->setRank(calculateNodeRank(node));
		return balance(node);
	}

private:
	Node* MoveNode(Node* node, Node** parent)
	{
		Node* sibling = (*parent)->getRight();
		Node* lNephew = sibling->getLeft();
		Node* rNephew = sibling->getRight();

		if (isRed(lNephew))
		{
			//  case 4
			// lNephew가 red라는 뜻은 NULL이 아니라는 뜻 -> 안터진다.
			sibling = rotateRight(sibling);
			rNephew = sibling->getRight();
		}
		if (isRed(rNephew))
		{
			//  case 5
			Node* grandParent = rotateLeft(*parent);
			Node* parentSibling = grandParent->getRight();
			flipColor(*parent);
			flipColor(parentSibling);
			flipColor(node);
		}
		deleteNode(node);
		return NULL;
	}

	Node* UnionNode(Node* node, Node** parent)
	{
		Node* sibling = (*parent)->getRight();
		Node* lNephew = sibling->getLeft();
		Node* rNephew = sibling->getRight();

		// case2
		if (!isRed(*parent) && !isRed(sibling) && !isRed(lNephew) && !isRed(rNephew))
			flipColor(sibling);
		// case 1
		if (isRed(sibling))
		{
			rotateLeft(*parent);
			sibling = (*parent)->setRight();
			lNephew = sibling ? sibling->getLeft() : NULL;
			rNephew = sibling ? sibling->getRight() : NULL;
		}
		// case 3
		if (isRed(*parent) && !isRed(sibling) && !isRed(lNephew) && !isRed(rNephew))
		{
			flipColor(*parent);
			flipColor(sibling);
			flipColor(node);  // -> 여기서 node가 red node가 됨.
		}
		deleteNode(node);
		return NULL;
	}

	// TODO: 확인 필요
	Node* balance(Node* node)
	{
		Node* tmp;

		if (isRed(node->getLeft()->getColor()))
		{
			if (isRed(node->getLeft()->getRight()->getColor()))
				node->setLeft(rotateLeft(node->getLeft()));  // LR
			if (isRed(node->getLeft()->getLeft()->getColor()))
				tmp = rotateRight(node);  // LL
		}
		else if (isRed(node->getRight()->getColor()))
		{
			if (isRed(node->getRight()->getLeft()->getColor()))
				node->setRight(rotateRight(node->getRight()));  // RL
			if (isRed(node->getRight()->getRight()->getColor()))
				tmp = rotateLeft(node);  // RR
		}
		return tmp;
	}

	bool isLeafNode(Node* node) const
	{
		if (!node->getLeft() && !node->getRight())
			return true;
		return false;
	}

	Node* swapValue(Node* lhs, Node* rhs)
	{
		value_type tmp = lhs->getValue();
		lhs->setValue(rhs->getValue());
		rhs->setValue(tmp);
		return lhs;
	}

	Node* getMinParentNodeFrom(Node* node) const
	{
		if (node->getLeft()->getLeft() == NULL)
			return node;
		return (getMinParentNodeFrom(node->getLeft()));
	}

	Node* createNode(const value_type& value = value_type())
	{
		Node* newNode = rb_node_allocator_.allocate(1);
		rb_node_allocator_.construct(newNode, rb_node_value_type(value));
		newNode->setColor(RED);
		return newNode;
	}

	void deleteNode(Node* node)
	{
		rb_node_allocator_.destroy(node);
		rb_node_allocator_.deallocate(node, 1);
	}

protected:
	/**
	 * @description: map range constructor에서 최적화 할 때 사용됨.
	 * 정렬된 데이터를 map으로 옮길 때, 어디에 넣을지에 대한 결정을 미리 할 수 있기에
	 * 전체 삽입 시간을 O(N)에 맞출 수 있다.
	 */
	Node* insert(Node* node, const value_type& value, const Color& color)  // node know where itself insert into
	{
		if (node == NULL)
		{
			Node* newNode = createNode(value);
			newNode->setColor(color);
			return (newNode);
		}
		if (node->getValue() < value)
			node->setRight(insert(node->getRight(), value, color));
		else if (value < node->getValue())
			node->setLeft(insert(node->getLeft(), value, color));
		node->setRank(calculateNodeRank(node));
		return node;
	}
};

#endif