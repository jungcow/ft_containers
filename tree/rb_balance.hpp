#ifndef __FT_RB_BALANCE_H__
#define __FT_RB_BALANCE_H__

#include "../type.hpp"  // TODO: 지우기
#include "node_wrapper.hpp"

template <class N>
class ft::NodeWrapper<N>::RBBalance : public TNode<RBBalance>::type
{
private:
	// friend class NodeWrapper;  // TODO: 안써도 되는지 체크하기
	typedef RBBalance Node;

public:
	enum Color
	{
		Red,
		Black,
		DoubleBlack
	};

	/**
	 * Base Type
	 */
	typedef typename TNode<RBBalance>::type base_node;
	typedef typename base_node::allocator_type allocator_type;

	typedef typename allocator_type::value_type value_type;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::size_type size_type;
	typedef typename allocator_type::difference_type difference_type;

public:  // TODO: 지정자 확인하기
	/**
	 * RB Node Type
	 */
	typedef typename allocator_type::template rebind<RBBalance>::other node_allocator_type;
	typedef typename node_allocator_type::value_type node_value_type;
	typedef typename node_allocator_type::pointer node_pointer;
	typedef typename node_allocator_type::reference node_reference;
	typedef typename node_allocator_type::const_pointer node_const_pointer;
	typedef typename node_allocator_type::const_reference node_const_reference;

	typedef typename node_allocator_type::size_type node_size_type;
	typedef typename node_allocator_type::difference_type node_difference_type;

private:
	Node* left_;
	Node* right_;
	Color color_;
	bool Nil_;
	node_allocator_type rb_node_allocator_;

public:
	RBBalance()
		: base_node(),
		  left_(NULL),
		  right_(NULL),
		  color_(Red),
		  Nil_(false),
		  rb_node_allocator_(node_allocator_type())
	{
	}

	RBBalance(const value_type& value, const Color& color = Red)
		: base_node(value),
		  left_(NULL),
		  right_(NULL),
		  color_(color),
		  Nil_(false),
		  rb_node_allocator_(node_allocator_type())
	{
	}

	RBBalance(const RBBalance& other)
		: base_node(other),
		  left_(other.getLeft()),
		  right_(other.getRight()),
		  color_(other.getColor()),
		  Nil_(other.isNil()),
		  rb_node_allocator_(node_allocator_type())
	{
	}

	~RBBalance()
	{
	}

	Node* getLeft(void) const
	{
		return (left_);
	}
	Node* getRight(void) const
	{
		return (right_);
	}

	Color getColor(void) const
	{
		return (color_);
	}

	bool isNil(void) const
	{
		return (Nil_);
	}

	void setLeft(Node* node)
	{
		left_ = node;
	}
	void setRight(Node* node)
	{
		right_ = node;
	}
	void setColor(const Color& color)
	{
		color_ = color;
	}

	void setNil(bool nil)
	{
		Nil_ = nil;
	}

	void flipColor(Node* node)
	{
		if (isRed(node))
			node->setColor(Black);
		else if (node->getColor() == Black)
			node->setColor(Red);
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
		if (node == NULL || node->getColor() != Red)
			return false;
		return true;
	}

	bool isLeftChild(Node* node, Node* parent) const
	{
		if (parent->getLeft() == node)
			return true;
		return false;
	}

	Node* rotateLeft(Node* node)
	{
		Node* tmp = node->getRight();

		node->setRight(tmp->getLeft());

		tmp->setLeft(node);
		tmp->setColor(node->getColor());
		tmp->setRank(node->getRank());

		node->setRank(this->calculateRankFrom(node));
		node->setColor(Red);
		return tmp;
	}

	Node* rotateRight(Node* node)
	{
		Node* tmp = node->getLeft();

		node->setLeft(tmp->getRight());

		tmp->setRight(node);
		tmp->setColor(node->getColor());
		tmp->setRank(node->getRank());

		node->setRank(this->calculateRankFrom(node));
		node->setColor(Red);
		return tmp;
	}

	Node* insert(Node* node, const value_type& value)
	{
		if (node == NULL)
			return (createNode(value));

		if (isRed(node->getLeft()) && isRed(node->getRight()))
			splitNode(node);
		// TODO: base_node:: 말고 this-> 로 고치기
		if (base_node::compareValue(node->getValue(), value))
			node->setRight(insert(node->getRight(), value));
		else if (base_node::compareValue(value, node->getValue()))
			node->setLeft(insert(node->getLeft(), value));
		node->setRank(this->calculateRankFrom(node));
		return balance(node);
	}

	Node* erase(Node* node, const value_type& value, Node* parent)
	{
		if (node == NULL)
			return NULL;

		if (base_node::compareValue(node->getValue(), value))
			node->setRight(erase(node->getRight(), value, node));
		else if (base_node::compareValue(value, node->getValue()))
			node->setLeft(erase(node->getLeft(), value, node));
		else
			return eraseImpl(node, value, parent);
		std::cout << "erase key: " << node->getValue().first << std::endl;
		std::cout << "erase parent key: " << parent->getValue().first << std::endl;
		node = fixup(node, parent);
		node->setRank(this->calculateRankFrom(node));
		return node;
	}

	Node* eraseImpl(Node* node, const value_type& value, Node* parent)
	{
		Node* toDel;
		Node* toDelChild;
		Node* toDelParent;
		Node* sibling;

		if (!node->getLeft() || !node->getRight())
		{
			toDel = node;

			toDelChild = toDel->getLeft() ? toDel->getLeft() : toDel->getRight();
			if (!toDelChild)
				toDelChild = createNilNode();
			toDelParent = parent;
			changeMyChild(toDel, toDelParent, toDelChild);
			if (!isRed(toDel) && !isRed(toDelChild))
				toDelChild->setColor(DoubleBlack);
			else if (isRed(toDel) && !isRed(toDelChild))
				toDelChild->setColor(Black);
			else if (!isRed(toDel) && isRed(toDelChild))
				toDelChild->setColor(Black);
			deleteNode(toDel);
			return (toDelChild);
		}
		else
		{
			toDel = getMinNodeFrom(node->getRight());
			toDelChild = getMinChildNodeFrom(node->getRight());
			if (!toDelChild)
				toDelChild = createNilNode();
			toDelParent = node;
			if (toDel != node->getRight())
				toDelParent = getMinParentNodeFrom(node->getRight());
			changeMyChild(toDel, toDelParent, toDelChild);

			if (!isRed(toDel) && !isRed(toDelChild))
				toDelChild->setColor(DoubleBlack);
			else if (isRed(toDel) && !isRed(toDelChild))
				toDelChild->setColor(Black);
			else if (!isRed(toDel) && isRed(toDelChild))
				toDelChild->setColor(Black);

			toDel->setLeft(node->getLeft());
			toDel->setRight(node->getRight());
			toDel->setColor(node->getColor());
			changeMyChild(node, parent, toDel);
			deleteNode(node);
			node = toDel;

			if (toDelChild->getColor() == DoubleBlack)
				node->setRight(postEraseImpl(node->getRight(), toDelChild->getValue(), node));
			node = fixup(node, parent);
			node->setRank(this->calculateRankFrom(node));
			return node;
		}
	}

public:
	Node* postEraseImpl(Node* node, const value_type& value, Node* parent)
	{
		if ((!this->compareValue(node->getValue(), value) &&
			 !this->compareValue(value, node->getValue())) ||
			node->isNil())
		{
			std::cout << std::boolalpha;
			std::cout << "post Erase Impl, is Nil? " << node->isNil() << std::endl;
			return node;
		}
		node->setLeft(postEraseImpl(node->getLeft(), value, parent));

		node = fixup(node, parent);
		node->setRank(this->calculateRankFrom(node));
		return node;
	}

	Node* fixup(Node* node, Node* parent)
	{
		std::cout << "fixup node key: " << node->getValue().first << std::endl;
		std::cout << "fixup node key color: " << node->getColor() << std::endl;
		if ((node->getLeft() && node->getLeft()->getColor() == DoubleBlack) ||
			(node->getRight() && node->getRight()->getColor() == DoubleBlack))
		{
			Node* toFixChild;
			if (node->getLeft() && node->getLeft()->getColor() == DoubleBlack)
				toFixChild = node->getLeft();
			else
				toFixChild = node->getRight();
			if (canMove(toFixChild, node))
			{
				std::cout << "can move!\n";
				return (moveNode(toFixChild, node));
			}
			std::cout << "only fusion!\n";
			return (fusionNode(toFixChild, node));
		}
		if (node->getLeft() && node->getLeft()->isNil())
		{
			deleteNode(node->getLeft());
			node->setLeft(NULL);
		}
		else if (node->getRight() && node->getRight()->isNil())
		{
			deleteNode(node->getLeft());
			node->setRight(NULL);
		}
		return node;
	}

	bool canMove(Node* node, Node* parent)
	{
		Node* sibling = getSiblingNode(node, parent);

		if (isRed(sibling->getLeft()) || isRed(sibling->getRight()))
			return true;
		return false;
	}

	Node* moveNode(Node* node, Node* parent)
	{
		Node* sibling = getSiblingNode(node, parent);
		Node* nearNephew = getNearNephewNode(sibling, parent);
		Node* farNephew = getFarNephewNode(sibling, parent);
		bool isLeft = isLeftChild(node, parent);

		std::cout << "move operation start\n";
		if (isRed(nearNephew) && !isRed(farNephew))
		{  //  case 4
			std::cout << "case 4\n";
			if (isLeft)
			{
				sibling = rotateRight(sibling);
				parent->setRight(sibling);
			}
			else
			{
				sibling = rotateLeft(sibling);
				parent->setLeft(sibling);
			}
			farNephew = getFarNephewNode(sibling, parent);
		}

		Node* grandParent;
		Node* parentSibling;
		if (isRed(farNephew))
		{  //  case 5
			std::cout << "case 5\n";
			if (isLeft)
				grandParent = rotateLeft(parent);
			else
				grandParent = rotateRight(parent);
			// std::cout << "move operation: rotate left(" << parent->getValue().first << ")\n";
			// std::cout << "move operation: grand parent(" << grandParent->getValue().first << ")\n";
			parentSibling = getSiblingNode(parent, grandParent);
			parent->setColor(Black);
			parentSibling->setColor(Black);
			(node)->setColor(Black);  // double black에서 black으로 완화시키기
			std::cout << "move operation done\n";
		}
		if ((node)->isNil())
		{
			std::cout << "is nil node\n";
			deleteNode(node);
			if (isLeft)
				parent->setLeft(NULL);
			else
				parent->setRight(NULL);
			return grandParent;
		}
		std::cout << "move operation really done\n";
		return grandParent;
	}

	Node* fusionNode(Node* node, Node* parent)
	{
		Node* sibling = getSiblingNode(node, parent);
		Node* nearNephew = getNearNephewNode(sibling, parent);
		Node* farNephew = getFarNephewNode(sibling, parent);
		Node* grandParent;
		bool isLeft = isLeftChild(node, parent);

		std::cout << "fusion operation start\n";
		// case2
		if (!isRed(parent) && !isRed(sibling) && !isRed(nearNephew) && !isRed(farNephew))
		{
			std::cout << "case2\n";
			parent->setColor(DoubleBlack);
			sibling->setColor(Red);
			(node)->setColor(Black);
			if ((node)->isNil())
			{
				std::cout << "is Nil Node\n";
				deleteNode(node);
				std::cout << "case2 end\n";
				if (isLeft)
					parent->setLeft(NULL);
				else
					parent->setRight(NULL);
				return parent;
			}
			std::cout << "case2\n";
			return parent;
		}
		// case 1
		if (isRed(sibling))
		{
			std::cout << "case1\n";
			if (isLeft)
				grandParent = rotateLeft(parent);
			else
				grandParent = rotateRight(parent);
			sibling = getSiblingNode(node, parent);
			nearNephew = getNearNephewNode(sibling, parent);
			farNephew = getFarNephewNode(sibling, parent);
			// case4또는 case5가 되는지를 확인. 안되면 case3번으로 감
			if (canMove(node, parent))
				return moveNode(node, parent);  // TODO: grand parent 호출해야 하는 거 아닌가?
		}
		// case 3
		if (isRed(parent) && !isRed(sibling) && !isRed(nearNephew) && !isRed(farNephew))
		{
			std::cout << "case3\n";
			parent->setColor(Black);
			sibling->setColor(Red);
			(node)->setColor(Black);
			if ((node)->isNil())
			{
				std::cout << "case 3 I'm NIL Node\n";
				deleteNode(node);
				std::cout << "parent key: " << parent->getValue().first << std::endl;
				if (isLeft)
					parent->setLeft(NULL);
				else
					parent->setRight(NULL);
				return grandParent;
				// return parent;
			}
		}
		return grandParent;
	}

	Node* balance(Node* node)
	{
		Node* tmp = node;

		if (isRed(node->getLeft()))
		{
			if (isRed(node->getLeft()->getRight()))
				node->setLeft(rotateLeft(node->getLeft()));  // LR
			if (isRed(node->getLeft()->getLeft()))
				tmp = rotateRight(node);  // LL
		}
		else if (isRed(node->getRight()))
		{
			if (isRed(node->getRight()->getLeft()))
				node->setRight(rotateRight(node->getRight()));  // RL
			if (isRed(node->getRight()->getRight()))
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

	Node* getSiblingNode(Node* node, Node* parent)
	{
		Node* sibling;

		if (isLeftChild(node, parent))
			sibling = parent->getRight();
		else
			sibling = parent->getLeft();
		return sibling;
	}

	Node* getNearNephewNode(Node* sibling, Node* parent)
	{
		if (isLeftChild(sibling, parent))
			return sibling->getRight();
		return sibling->getLeft();
	}
	Node* getFarNephewNode(Node* sibling, Node* parent)
	{
		if (isLeftChild(sibling, parent))
			return sibling->getLeft();
		return sibling->getRight();
	}

	/**
	 * @param myChild: my child
	 * @param me: parent of myChild
	 * @param otherChild: to be my child soon
	 */
	void changeMyChild(Node* myChild, Node* me, Node* otherChild)
	{
		if (isLeftChild(myChild, me))
			me->setLeft(otherChild);
		else
			me->setRight(otherChild);
	}

	Node* getMinParentNodeFrom(Node* node) const
	{
		if (!node->getLeft())
			return NULL;  // 노드 바로 아래가 minNode일 경우
		if (node->getLeft()->getLeft() == NULL)
			return node;
		return (getMinParentNodeFrom(node->getLeft()));
	}

	Node* getMinChildNodeFrom(Node* node) const
	{
		if (!node->getLeft())
			return node->getRight();
		return (getMinChildNodeFrom(node->getLeft()));
	}

	Node* createNode(const value_type& value = value_type())
	{
		Node* newNode = rb_node_allocator_.allocate(1);
		rb_node_allocator_.construct(newNode, node_value_type(value));
		return newNode;
	}

	Node* createNilNode(const Color& color = Black)
	{
		Node* newNode = rb_node_allocator_.allocate(1);
		rb_node_allocator_.construct(newNode, node_value_type(value_type()));
		newNode->setNil(true);
		newNode->setColor(Black);
		return newNode;
	}

	void deleteNode(Node* node)
	{
		rb_node_allocator_.destroy(node);
		rb_node_allocator_.deallocate(node, 1);
	}

	void deleteAllNodes(Node* node)
	{
		if (node == NULL)
			return;
		deleteAllNodes(node->getRight());
		deleteAllNodes(node->getLeft());
		rb_node_allocator_.destroy(node);
		rb_node_allocator_.deallocate(node, 1);
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
		node->setRank(this->calculateRankFrom(node));
		return node;
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
		if (base_node::compareValue(node->getValue(), value))
			node->setRight(insert(node->getRight(), value, color));
		else if (base_node::compareValue(value, node->getValue()))
			node->setLeft(insert(node->getLeft(), value, color));
		node->setRank(this->calculateRankFrom(node));
		return node;
	}
};

#endif
