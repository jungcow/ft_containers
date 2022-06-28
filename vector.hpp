#ifndef __FT_VECTOR_H__
# define __FT_VECTOR_H__

# include <memory>

namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef Alloc									allocator_type;

	public:
        typedef T										value_type;

        typedef value_type&								reference;
        typedef const value_type&						const_reference;

		typedef value_type*								pointer;
		typedef const value_type*						const_pointer;

# if 0
		typedef ft::vector_iterator<pointer, vector>		iterator;
		typedef ft::vector_iterator<const_pointer, vector>	const_iterator;

		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
# endif
		typedef typename allocator_type::size_type		size_type;

	public: 
# if 0
		explicit vector (const allocator_type& alloc = allocator_type());
		explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type());
		template <class InputIterator>
         vector (InputIterator first, InputIterator last,
                 const allocator_type& alloc = allocator_type());
		vector (const vector& x);
# endif

# if 0
	public:
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last) {}
		void assign(size_type n, const value_type& val) {}

		reference at (size_type n) {}
		const_reference at (size_type n) const {}

		reference back() {}
		const_reference back() const {}

vector& operator= (const vector& x) {}
reference operator[] (size_type n) {}
const_reference operator[] (size_type n) const {}
iterator begin() {}
const_iterator begin() const {}
size_type capacity() const {}
size_type capacity() const {}
void clear() {}
bool empty() const {}
iterator end() {}
const_iterator end() const {}
iterator erase (iterator position) {}
iterator erase (iterator first, iterator last) {}
reference front() {}
const_reference front() const {}
allocator_type get_allocator() const {}
iterator insert (iterator position, const value_type& val) {}
void insert (iterator position, size_type n, const value_type& val) {}
template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last) {}
size_type max_size() const {}
void pop_back() {}
void push_back (const value_type& val) {}
reverse_iterator rbegin() {}
const_reverse_iterator rbegin() const {}
reverse_iterator rend() {}
const_reverse_iterator rend() const {}
void reserve (size_type n) {}
void resize (size_type n, value_type val = value_type()) {}
size_type size() const {}
void swap (vector& x) {}
# endif
	};
# if 0
template <class T, class Alloc>
  bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {}
template <class T, class Alloc>
  bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {}
template <class T, class Alloc>
  bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {}
template <class T, class Alloc>
  bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {}
template <class T, class Alloc>
  bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {}
template <class T, class Alloc>
  bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {}
template <class T, class Alloc>
  void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {}
# endif
};

#endif
