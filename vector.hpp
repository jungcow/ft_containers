#ifndef __FT_VECTOR_H__
#define __FT_VECTOR_H__

#include <memory>

#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft
{
	template <class Iter, class Pointer>
	class vector_iterator;

	template <typename T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef Alloc allocator_type;

	public:
		typedef typename allocator_type::value_type value_type;

		typedef value_type& reference;
		typedef const value_type& const_reference;

		typedef value_type* pointer;
		typedef const value_type* const_pointer;

		typedef ft::vector_iterator<pointer, pointer> iterator;
		typedef ft::vector_iterator<const_pointer, pointer> const_iterator;
#if 0

		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
#endif
		typedef typename allocator_type::size_type size_type;

	public:
#if 0
		explicit vector (const allocator_type& alloc = allocator_type());
		explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type());
		template <class InputIterator>
         vector (InputIterator first, InputIterator last,
                 const allocator_type& alloc = allocator_type());
		vector (const vector& x);
#endif

#if 0
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
#endif
	};
#if 0
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
#endif

	template <class Iterator, class Pointer>
	class vector_iterator
	{
	private:
		typedef ft::iterator_traits<Iterator> traits;
		typedef typename traits::value_type value_type;
		typedef typename traits::pointer pointer;
		typedef typename traits::reference reference;
		typedef typename traits::difference_type difference_type;
		typedef typename traits::iterator_category iterator_category;

	private:
		Iterator base_;

	public:
		vector_iterator() {}

		/**
		 * Copy Constructor
		 * ft::is_same의 두번째 템플릿 인자는 복사 생성에 이용하는 iterator의 type을 의미한다.
		 * i) const_iterator = iterator (O)
		 * ii) iterator = const_iterator (X)
		 * 위와 같은 상황을 고려하여 is_same 두번째 인자에 const가 올 때에는 허용을 하도록 해야 한다(위 첫번째 경우에 해당한다.)
		 * _Up는 무조건 비상수 iterator, Container::pointer는 상수든 아니든 Container의 pointer를 가져오기 때문에 비상수.
		 * 때문에 is_same의 value가 1이 되면서 enable_if의 type이 Container로 정의되어 진다.
		 */
		template <class P /*pointer를 받는다. */>
		vector_iterator(const vector_iterator<P, typename ft::enable_if<
													 ft::is_same<P, Pointer>::value,
													 Pointer>::type>& other)
			: base_(other.base())
		{
			std::cout << "copy constructor of vector iterator\n";
		}

		/**
		 * can be assigned by same type
		 * 복사 생성자 처럼 호환 가능한 것들을 인자로 받을 필욘 없음
		 */
		template <class P>
		vector_iterator& operator=(const vector_iterator& other)
		{
			base_ = other.base_;
			return (*this);
		}

		/**
		 * pointer를 보관만 하기 때문에 destructor의 본문이 없음
		 */
		~vector_iterator() {}

		/**
		 * lvalue로도 되어야 하고 rvalue로도 되어야 하므로
		 * reference를 반환하므로 lvalue가 될 수도 있게 된다.
		 */
		reference operator*() const
		{
			return (*base_);
		}

		/**
		 * iterator가 가리키는 값의 멤버 함수 및 멤버 변수를 자신의 것인 마냥 접근할 수 있다.
		 */
		pointer operator->() const
		{
			return &(*base_);
		}
		reference& operator[](int n) const
		{
			return base_[n];
		}
		Iterator base(void) const
		{
			return base_;
		}

		vector_iterator& operator++()
		{
			++base_;
			return (*this);
		}
		vector_iterator operator++(int)
		{
			vector_iterator tmp = *this;
			++(*this);
			return (tmp);
		}

		vector_iterator operator+(int n) const
		{
			vector_iterator tmp = *this;

			tmp.base_ += n;
			return (tmp);
		}
		vector_iterator operator-(int n) const
		{
			vector_iterator tmp = *this;

			tmp.base_ -= n;
			return (tmp);
		}
		difference_type operator-(const vector_iterator& other) const
		{
			return (base_ - other.base());
		}

		vector_iterator operator+=(int n)
		{
			*this = *this + n;
			return (*this);
		}
		vector_iterator operator-=(int n)
		{
			*this = *this - n;
			return (*this);
		}
		/**
		 * 두 iterator가 같다 => 두 iterator 값이 동일한 sequence를 반복한다(순회한다)
		 */
		bool operator==(const vector_iterator& other) const
		{
			return (base_ == other.base_);
		}
		bool operator!=(const vector_iterator& other) const
		{
			return !(base_ == other.base_);
		}

		bool operator<(const vector_iterator& other) const
		{
			return (base_ < other.base());
		}
		bool operator>(const vector_iterator& other) const
		{
			return (base_ > other.base());
		}
		bool operator<=(const vector_iterator& other) const
		{
			return (base_ <= other.base());
		}
		bool operator>=(const vector_iterator& other) const
		{
			return (base_ >= other.base());
		}

		template <class Iter, class P>
		friend vector_iterator<Iter, P> operator+(int n, const vector_iterator<Iter, P>& other);
	};

	template <class Iter, class P>
	vector_iterator<Iter, P> operator+(int n, const vector_iterator<Iter, P>& other)
	{
		return (other + n);
	}
}

#endif
