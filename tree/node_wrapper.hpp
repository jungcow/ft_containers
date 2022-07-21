#ifndef __FT_TREE_H__
#define __FT_TREE_H__

#include "node.hpp"

namespace ft
{
	template <class N>
	struct NodeWrapper
	{
		// class AVLBalance;
		// class LLRBBalance;

	private:
		template <class Balance>
		struct TNode
		{
			typedef ft::node::Node<N, Balance> type;
		};

		class RBBalance;

	public:
		typedef typename TNode<RBBalance>::type RBNode;
		// typedef typename TNode<AVLBalance>::type AVLNode;

		typedef RBBalance BalanceNode;
	};
}

#endif
