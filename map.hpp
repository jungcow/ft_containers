#ifndef __FT_MAP_H__
#define __FT_MAP_H__

#include <cstddef>     // ptrdiff_t
#include <functional>  // std::less, std::binary_function

#include "iterator.hpp" // ft::reverse_iterator
#include "utility.hpp" // ft::pair

namespace ft
{
	template <class T>
	class map_iterator;

	template <class Key,
			  class T,
			  class Compare = std::less<Key>,
			  class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	private:
	public:
		typedef Key 									key_type;
		typedef T 										mapped_type;
		typedef ft::pair<const key_type, mapped_type>	value_type;

		typedef Compare									key_compare;
		class value_compare : public std::binary_function<value_type, value_type, bool>  // TODO : 마저 완성하기
		{
		public: 
			bool operator()(const value_type& lhs, const value_type& rhs) const
			{
				return comp(lhs.first, rhs.first);
			}
		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {}
		};

		typedef Alloc									allocator_type;
		typedef ptrdiff_t								difference_type;
		typedef size_t									size_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef typename allocator_type::pointer		pointer;
		typedef typename allocator_type::const_pointer	const_pointer;
		typedef map_iterator<value_type>				iterator;
		typedef map_iterator<const value_type>			const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

#if 0
		explicit map(const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
		{

		} // comparison object도 같이 설정
 
		template <class InputIterator>
		map(InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type());

		map(const map& x);
		~map();

#endif
#if 0
		iterator begin();
		const_iterator begin() const;

		void clear();
		size_type count(const key_type& k) const;

		bool empty() const;

		iterator end();
		const_iterator end() const;

		ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const;
		ft::pair<iterator, iterator> equal_range(const key_type& k);

		void erase(iterator position);
		size_type erase(const key_type& k);
		void erase(iterator first, iterator last);

		iterator find(const key_type& k);
		const_iterator find(const key_type& k) const;

		allocator_type get_allocator() const;

		ft::pair<iterator, bool> insert(const value_type& val);
		iterator insert(iterator position, const value_type& val);
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last);

		key_compare key_comp() const;

		iterator lower_bound(const key_type& k);
		const_iterator lower_bound(const key_type& k) const;

		size_type max_size() const;

		map& operator=(const map& x);

		mapped_type& operator[](const key_type& k);

		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;

		reverse_iterator rend();
		const_reverse_iterator rend() const;

		size_type size() const;

		void swap(map& x);

		iterator upper_bound(const key_type& k);
		const_iterator upper_bound(const key_type& k) const;

		value_compare value_comp() const;

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
	template <class T>
	class map_iterator
	{
	};
}

#endif
