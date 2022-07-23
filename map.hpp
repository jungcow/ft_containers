#ifndef __FT_MAP_H__
#define __FT_MAP_H__

#include <cstddef>     // ptrdiff_t
#include <functional>  // std::less, std::binary_function

#include "iterator.hpp"  // ft::reverse_iterator
#include "tree/node_base.hpp"
#include "tree/node_wrapper.hpp"
#include "tree/tree.hpp"
#include "type.hpp"     // TODO: type 출력, 디버깅용
#include "utility.hpp"  // ft::pair

namespace ft
{
	template <class Iterator, class NodePointer, class TreePointer, class VIter, class VPointer>
	class map_iterator;

	template <class Key,
			  class T,
			  class Compare = std::less<Key>,
			  class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	private:
		template <class Iterator, class NodePointer, class TreePointer, class VIter, class VPointer>
		friend class ft::map_iterator;

	public:
		/**
		 * Map Inner Type
		 */
		typedef Key key_type;
		typedef T mapped_type;

		typedef Compare key_compare;
		class value_compare;

		typedef Alloc allocator_type;

		typedef typename allocator_type::size_type size_type;
		typedef typename allocator_type::difference_type difference_type;

		typedef typename allocator_type::value_type value_type;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::const_reference const_reference;

	private:
		/**
		 * Node and Tree type
		 */
		typedef ft::node::NodeBase<pointer, pointer, value_compare, allocator_type> node_base;
		typedef ft::node::NodeBase<const_pointer, pointer, value_compare, allocator_type> const_node_base;

		typedef typename ft::NodeWrapper<node_base>::RBNode node_type;
		typedef typename ft::NodeWrapper<const_node_base>::RBNode const_node_type;

		typedef typename ft::NodeWrapper<node_base>::node_allocator_type node_allocator_type;
		typedef typename ft::NodeWrapper<node_base>::node_size_type node_size_type;
		typedef typename ft::NodeWrapper<node_base>::node_value_type node_value_type;
		// typedef typename ft::NodeWrapper<node_base>::BalanceNode balance_node_type;

		typedef ft::Tree<node_type> map_tree;

		typedef typename node_type::iterator node_iterator;
		typedef typename const_node_type::iterator const_node_iterator;

	public:
		/**
		 * iterator type
		 */
		typedef map_iterator<node_iterator, node_type*, map_tree*, pointer, pointer> iterator;
		typedef map_iterator<const_node_iterator, const_node_type*, map_tree*, const_pointer, pointer> const_iterator;

		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	private:
		map_tree data_;
		key_compare compare_key_;
		size_type size_;
		allocator_type allocator_;

	public:
		explicit map(const key_compare& comp = key_compare(),
					 const allocator_type& alloc = allocator_type())
			: compare_key_(comp), size_(0), allocator_(alloc)
		{
		}

#if 0
		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
		{
			for (; first != last; first++)
				data_.insert(*first);
		}

		map(const map& x)
		{
			// level tranverse
		}
		~map();

#endif
		iterator begin()
		{
			return iterator(data_.getFirst(), &data_);
		}
		const_iterator begin() const
		{
			return const_iterator(data_.getFirst(), &data_);
		}

#if 0
		void clear();
#endif
		size_type count(const key_type& k) const
		{
			if (data_.find(ft::make_pair(k, mapped_type())))
				return 1;
			return 0;
		}

		bool empty() const
		{
			return data_.empty();
		}
		iterator end()
		{
			return iterator(data_.getLast(), &data_);
		}
		const_iterator end() const
		{
			return const_iterator(data_.getLast(), &data_);
		}
#if 0

		ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const;
		ft::pair<iterator, iterator> equal_range(const key_type& k);

		void erase(iterator position);
#endif
		size_type erase(const key_type& k)
		{
			size_type i = data_.erase(ft::make_pair(k, mapped_type()));
			std::cout << std::boolalpha;
			std::cout << "is all alright? " << data_.isFollowedAllRules() << std::endl;
			return i;
		}
#if 0
		void erase(iterator first, iterator last);

		iterator find(const key_type& k);
		const_iterator find(const key_type& k) const;

#endif
		allocator_type get_allocator() const
		{
			return allocator_;
		}

		ft::pair<iterator, bool> insert(const value_type& val)
		{
			ft::pair<iterator, bool> res = ft::make_pair(iterator(data_.insert(val), &data_), true);
			std::cout << std::boolalpha;
			std::cout << "is all alright? " << data_.isFollowedAllRules() << std::endl;
			return res;
		}

		// iterator insert(iterator position, const value_type& val)
		// {
		// }
#if 0
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last);
#endif
		key_compare key_comp() const
		{
			return compare_key_;
		}

#if 0
		iterator lower_bound(const key_type& k);
		const_iterator lower_bound(const key_type& k) const;
#endif
		size_type max_size() const throw()
		{
			return (std::numeric_limits<node_size_type>::max() /
					std::max(2, static_cast<int>(sizeof(node_value_type))));
		}
#if 0
		map& operator=(const map& x);
#endif
		mapped_type& operator[](const key_type& k)
		{
			return (*((this->insert(make_pair(k, mapped_type()))).first)).second;
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		size_type size() const
		{
			return data_.size();
		}

		void print() const
		{
			data_.printByInOrderTraversal();
		}
#if 0

		void swap(map& x);

		iterator upper_bound(const key_type& k);
		const_iterator upper_bound(const key_type& k) const;
#endif
		value_compare value_comp() const
		{
			return (value_compare(compare_key_));
		}
#if 0
		template <class K, class V, class Comp, class A>
		friend bool operator==(const map<K, V, Comp, A>& lhs,
				const map<K, V, Comp, A>& rhs);
		template <class K, class V, class Comp, class A>
		friend bool operator!=(const map<K, V, Comp, A>& lhs,
				const map<K, V, Comp, A>& rhs);
		template <class K, class V, class Comp, class A>
		friend bool operator<(const map<K, V, Comp, A>& lhs,
				const map<K, V, Comp, A>& rhs);
		template <class K, class V, class Comp, class A>
		friend bool operator<=(const map<K, V, Comp, A>& lhs,
				const map<K, V, Comp, A>& rhs);
		template <class K, class V, class Comp, class A>
		friend bool operator>(const map<K, V, Comp, A>& lhs,
				const map<K, V, Comp, A>& rhs);
		template <class K, class V, class Comp, class A>
		friend bool operator>=(const map<K, V, Comp, A>& lhs,
				const map<K, V, Comp, A>& rhs);
#endif
	};

#if 0
	template <class K, class V, class Comp, class A>
	bool operator==(const map<K, V, Comp, A>& lhs,
			const map<K, V, Comp, A>& rhs);
	template <class K, class V, class Comp, class A>
	bool operator!=(const map<K, V, Comp, A>& lhs,
		const map<K, V, Comp, A>& rhs);
	template <class K, class V, class Comp, class A>
	bool operator<(const map<K, V, Comp, A>& lhs,
			const map<K, V, Comp, A>& rhs);
	template <class K, class V, class Comp, class A>
	bool operator<=(const map<K, V, Comp, A>& lhs,
			const map<K, V, Comp, A>& rhs);
	template <class K, class V, class Comp, class A>
	bool operator>(const map<K, V, Comp, A>& lhs,
			const map<K, V, Comp, A>& rhs);
	template <class K, class V, class Comp, class A>
	bool operator>=(const map<K, V, Comp, A>& lhs,
			const map<K, V, Comp, A>& rhs);
#endif

	/**
	 * @class: value_compare
	 *
	 * @param Iterator: a key to find value
	 * @param T: a value, are paired with Key type
	 * @param Compare: class comparator for compare Keys
	 * @param Alloc: allocator for allocate value type which is ft::pair<Key, T> type
	 */
	template <class Key,
			  class T,
			  class Compare,
			  class Alloc>
	class map<Key, T, Compare, Alloc>::value_compare : public std::binary_function<value_type, value_type, bool>
	{
	private:
		friend class map;
		friend class ft::node::NodeBase<value_type*, value_type*, value_compare, Alloc>;

	public:
		bool operator()(const value_type& lhs, const value_type& rhs) const
		{
			return comp(lhs.first, rhs.first);
		}

	protected:
		Compare comp;
		value_compare(Compare c) : comp(c) {}
		value_compare() : comp(Compare()) {}
	};

	/**
	 * @class map_iterator
	 *
	 * @param Iterator: node iterator
	 * @param VIter: value iterator, here is ft::pair<Key, T>
	 * @param VPointer: value pointer, used to be compatible with const pointer
	 */
	template <class Iterator, class NodePointer, class TreePointer, class VIter, class VPointer>
	class map_iterator
	{
	private:
		typedef typename Iterator::inner_value_type inner_value_type;
		typedef typename Iterator::inner_pointer inner_pointer;
		typedef typename Iterator::inner_reference inner_reference;
		typedef typename Iterator::const_inner_pointer const_inner_pointer;
		typedef typename Iterator::const_inner_reference const_inner_reference;

	public:
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::iterator_category iterator_category;

	private:
		Iterator base_;  // Iterator: node_iterator
		TreePointer tree_;
		size_t order_;

	public:
		map_iterator() : order_(0)
		{
		}

		template <class Iter, class Np, class Tp, class I>
		map_iterator(const map_iterator<
					 Iter, Np, Tp, I, typename ft::enable_if<ft::is_same<I, VPointer>::value, VPointer>::type>& other)
			: base_(other.base()), tree_(other.tree()), order_(other.order())
		{
		}

		explicit map_iterator(const Iterator& otherIter, const TreePointer& tree)  // node_iterator로 생성
			: base_(otherIter), tree_(tree)
		{
			//TODO: order 구하기
			order_ = tree_.getOrder(*base);
		}

		explicit map_iterator(const NodePointer& node, const TreePointer& tree)  // node_iterator로 생성
			: base_(node), tree_(tree)
		{
			order_ = tree_.getOrder(*base);
		}

		map_iterator& operator=(const map_iterator& other)
		{
			base_ = other.base_;
			tree_ = other.tree_;
			order_ = other.order_;
			return (*this);
		}

		~map_iterator() {}

		Iterator base(void) const
		{
			return base_;
		}
		TreePointer tree(void) const
		{
			return tree_;
		}
		size_t order(void) const
		{
			return order_;
		}

		const_inner_reference operator*() const
		{
			return (*base_);
		}

		inner_reference operator*()
		{
			return (*base_);
		}

		inner_pointer operator->() const
		{
			return (base_.operator->());
		}

		map_iterator& operator++()
		{
			size_t rank = base_.left()
							  ? base_.left()->getRank() + 1
							  : 1;
			// std::cout << "before: " << (*base_).first << "(" << rank << ")" << std::endl;
			base_ = Iterator(tree_->OS_Select(tree_->getRoot()->getLeft(), rank + 1));
			if (base_.left())
				rank = base_.left()->getRank() + 1;
			else
				rank = 1;
			std::cout << "after: " << (*base_).first << "(" << rank << ")" << std::endl;
			return (*this);
		}
		map_iterator operator++(int)
		{
			map_iterator tmp = *this;
			++(*this);
			return (tmp);
		}
		/**
		 * ++a, a++, *a++
		 * --a, a--, *a--
		 */

		// template <class Iter, class Np, class Vi, class Vp>
		// friend bool operator==(const map_iterator<Iter, Np, Vi, Vp>& lhs, const map_iterator<Iter, Np, Vi, Vp>& rhs);
		// template <class Iter, class Np, class Vi, class Vp>
		// friend bool operator!=(const map_iterator<Iter, Np, Vi, Vp>& lhs, const map_iterator<Iter, Np, Vi, Vp>& rhs);
	};
	// template <class Iter, class Np, class Vi, class Vp>
	// bool operator==(const map_iterator<Iter, Np, Vi, Vp>& lhs, const map_iterator<Iter, Np, Vi, Vp>& rhs)
	// {
	// 	return (lhs.base_ == rhs.base_);
	// }
	// template <class Iter, class Np, class Vi, class Vp>
	// bool operator!=(const map_iterator<Iter, Np, Vi, Vp>& lhs, const map_iterator<Iter, Np, Vi, Vp>& rhs)
	// {
	// 	return !(lhs == rhs);
	// }
}

#endif
