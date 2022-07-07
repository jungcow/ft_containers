#ifndef __FT_VECTOR_H__
#define __FT_VECTOR_H__

#include <algorithm>  // std::min, std::max
#include <exception>  // bad_alloc, length_error, out_of_range
#include <iostream>   //temporary include TODO: 지우기
#include <iterator>   // std::distance
#include <memory>     // allocator

#include "algorithm.hpp"
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
		typedef typename allocator_type::size_type size_type;

		typedef value_type& reference;
		typedef const value_type& const_reference;

		typedef value_type* pointer;
		typedef const value_type* const_pointer;

		typedef ft::vector_iterator<pointer, pointer> iterator;
		typedef ft::vector_iterator<const_pointer, pointer> const_iterator;

		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	private:
		allocator_type allocator_;
		pointer data_;
		size_type size_;
		size_type capacity_;

	public:
		explicit vector(const allocator_type& alloc = allocator_type()) throw(std::bad_alloc)
			: allocator_(alloc), size_(0), capacity_(1)
		{
			if (capacity_ > max_size())
				throw std::bad_alloc();
			data_ = allocator_.allocate(sizeof(value_type) * capacity_);
		}
		explicit vector(size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type()) throw(std::bad_alloc)
			: allocator_(alloc), size_(n), capacity_(n + 1)
		{
			if (n > max_size())
				throw std::bad_alloc();
			data_ = allocator_.allocate(sizeof(value_type) * capacity_);
			for (size_type i = 0; i < size_; i++)
				allocator_.construct(&data_[i], val);
		}
		template <class InputIterator>
		vector(typename ft::enable_if<
				   !ft::is_integral<InputIterator>::value,
				   InputIterator>::type first,
			   InputIterator last, const allocator_type& alloc = allocator_type()) throw(std::bad_alloc)
			: allocator_(alloc)
		{
			if (ft::is_same<ft::input_iterator_tag,
							typename ft::iterator_traits<InputIterator>::iterator_category>::value)
			{
				size_ = 0;
				capacity_ = 1;
				data_ = allocator_.allocate(sizeof(value_type) * capacity_);
				for (; first != last; first++)
					push_back(*first);
			}
			else if (ft::is_base_of<ft::forward_iterator_tag,
									typename ft::iterator_traits<InputIterator>::iterator_category>::value)
			{
				size_type n = 0;
				if (ft::is_same<ft::random_access_iterator_tag,
								typename ft::iterator_traits<InputIterator>::iterator_category>::value)
				{
					n = last - first;
				}
				else
				{
					for (InputIterator start = first; start != last; start++)
						n++;
				}
				if (n > max_size())
				{
					throw std::bad_alloc();
				}
				size_ = n;
				capacity_ = n + 1;
				data_ = allocator_.allocate(sizeof(value_type) * capacity_);
				for (size_type i = 0; i < n; i++)
				{
					allocator_.construct(&data_[i], *first++);
				}
			}
		}
		vector(const vector& x) throw(std::bad_alloc)
			: allocator_(x.allocator_), size_(x.size_), capacity_(x.capacity_)
		{
			if (capacity_ > max_size())
				throw std::bad_alloc();
			data_ = allocator_.allocate(sizeof(value_type) * capacity_);
			for (size_type i = 0; i < size_; i++)
			{
				allocator_.construct(&data_[i], x.data_[i]);
			}
		}
		~vector()
		{
			// TODO: Trivial destructible 에 대해서 최적화 하기
			clear();
			allocator_.deallocate(data_, capacity_);
			size_ = 0;
			capacity_ = 0;
		}

	public:
		template <class InputIterator>
		void assign(typename ft::enable_if<
						!ft::is_integral<InputIterator>::value,
						InputIterator>::type first,
					InputIterator last) throw(std::bad_alloc)
		{
			if (ft::is_same<ft::input_iterator_tag,
							typename ft::iterator_traits<InputIterator>::iterator_category>::value)
			{
				clear();
				// TODO: 주석 확인하고 지우기
				//  allocator_.deallocate(data_, capacity_);

				// capacity_ = 1;
				// data_ = allocator_.allocate(sizeof(value_type) * capacity_);
				for (; first != last; first++)
					push_back(*first);
			}
			else if (ft::is_base_of<ft::forward_iterator_tag,
									typename ft::iterator_traits<InputIterator>::iterator_category>::value)
			{
				std::allocator<void>::const_pointer hint = &data_[0];
				size_type n = 0;
				if (ft::is_same<ft::random_access_iterator_tag, InputIterator>::value)
				{
					n = last - first;
				}
				else
				{
					for (InputIterator start = first; start != last; start++)
						n++;
				}
				if (capacity_ < n)
				{
					resize(n);
				}
				clear();
				data_ = allocator_.allocate((sizeof(value_type) * capacity_), hint);
				for (size_type i = 0; i < n; i++)
				{
					allocator_.construct(&data_[i], *first++);
				}
				size_ = n;
			}
		}
		
		void assign(size_type n, const value_type& val) throw(std::bad_alloc)
		{
			if (capacity_ < n)
				resize(n);
			clear();
			data_ = allocator_.allocate(sizeof(value_type) * capacity_, &data_[0]);
			for (size_type i = 0; i < n; i++)
				allocator_.construct(&data_[i], val);
			size_ = n;
		}

		reference at(size_type n) throw(std::out_of_range)
		{
			if (size_ <= n)
				throw std::out_of_range("at: out of range");
			return (data_[n]);
		}
		const_reference at(size_type n) const throw(std::out_of_range)
		{
			if (size_ <= n)
				throw std::out_of_range("at: out of range");
			return (data_[n]);
		}

		reference back()
		{
			return (data_[size_ - 1]);
		}
		const_reference back() const
		{
			return (data_[size_ - 1]);
		}

		iterator begin()
		{
			return iterator(&data_[0]);
		}
		const_iterator begin() const
		{
			return const_iterator(&data_[0]);
		}

		size_type capacity() const
		{
			return (capacity_);
		}

		void clear()
		{
			// size to 0, not modify capacity(not guaranted)
			/**
			 * TODO: destroy 하지 않아도 될 것들은 상수 시간내에 clear할 수 있음
			 */
			if (!ft::is_trivial_destructible_junior<value_type>::value)
			{
				for (size_type i = 0; i < size_; i++)
					allocator_.destroy(&data_[i]);
			}
			size_ = 0;
		}

		bool empty() const
		{
			return (size_ == 0);
		}

		iterator end()
		{
			return iterator(&data_[size_]);
		}
		const_iterator end() const
		{
			return const_iterator(&data_[size_]);
		}

		iterator erase(iterator position)
		{
			/**
			 * TODO:iterator의 위치가 잘못됐을 시, undefined behavior 발생
			 * -> 그러나 컨테이너느 valid한 상태로 나와야함
			 */
			if (position == end() - 1)
			{
				allocator_.destroy(&data_[size_ - 1]);
				size_--;
				return end();
			}
			iterator start = position;
			iterator ret = start;
			iterator finish = end();
			for (; start + 1 != finish; start++)
			{
				allocator_.destroy(&(*start));
				allocator_.construct(&(*start), (*(start + 1)));
			}
			allocator_.destroy(&(*start));
			size_--;
			return ret;
		}
		iterator erase(iterator first, iterator last)
		{
			size_type n = last - first;
			iterator start = first;
			iterator ret = first;
			iterator finish = last;
			for (; start + n != finish; start++)
			{
				allocator_.destroy(&(*start));
				allocator_.construct(&(*start), (*(start + n)));
			}
			for (; start != finish; start++)
			{
				allocator_.destroy(&(*start));
			}
			size_ -= n;
			return ret;
		}

		reference front()
		{
			return (data_[0]);
		}
		const_reference front() const
		{
			return (data_[0]);
		}

		allocator_type get_allocator() const
		{
			return (allocator_type(allocator_));
		}

		iterator insert(iterator position, const value_type& val)
		{
			size_type pos = 0;

			for (size_type i = size_; i <= 0; i--)
			{
				if (iterator(&data_[i]) == position)
					break;
				pos++;
			}
			if (size_ + 1 >= capacity_)
				resize(capacity_ * 2);
			allocator_.construct(&data_[size_], value_type());
			iterator start = end();
			iterator finish = end() - (pos);
			for (; start != finish; start--)
			{
				allocator_.construct(&(*start), *(start - 1));
				allocator_.destroy(&(*(start - 1)));
			}
			allocator_.construct(&(*start), val);
			size_++;
			return start;
		}
		void insert(iterator position, size_type n, const value_type& val)  // throw(std::bad_alloc)
		{
			size_type pos = 0;
			for (size_type i = size_; i <= 0; i--)
			{
				if (iterator(&data_[i]) == position)
					break;
				pos++;
			}
			if (size_ + n + 1 >= capacity_)
				resize(size_ + n + 1);
			for (size_type i = 0; i < n; i++)
			{
				allocator_.construct(&data_[size_ + i], value_type());
			}
			iterator start = end() + n - 1;
			iterator finish = end() - (pos);
			for (; start - (n - 1) != finish; start--)
			{
				allocator_.construct(&(*start), (*(start - n)));
				allocator_.destroy(&(*(start - n)));
			}
			for (size_type i = 0; i < n; i++, pos++)
			{
				allocator_.construct(&data_[pos - 1], val);
			}
			size_ += n;
		}

		template <class InputIterator>
		void insert(iterator position,
					typename ft::enable_if<
						!ft::is_integral<InputIterator>::value,
						InputIterator>::type first,
					InputIterator last) throw(std::bad_alloc)
		{
			if (ft::is_same<ft::input_iterator_tag,
							typename ft::iterator_traits<InputIterator>::iterator_category>::value)
			{
				vector tmp = *this;
				iterator start = begin();
				iterator finish = end();

				for (; start != position; start++)
					tmp.push_back(*start);
				for (; first != last; first++, start++)
					tmp.push_back(*first);
				for (; start != finish; start++)
					tmp.push_back(*start);
				clear();
				allocator_.deallocate(data_, capacity_);
				*this = tmp;
			}
			else if (ft::is_base_of<ft::forward_iterator_tag,
									typename ft::iterator_traits<InputIterator>::iterator_category>::value)
			{
				size_type pos = 0;
				for (size_type i = size_; i <= 0; i--)
				{
					if (iterator(&data_[i]) == position)
						break;
					pos++;
				}
				size_type n = 0;
				if (ft::is_same<ft::random_access_iterator_tag, InputIterator>::value)
					n = last - first;
				else
				{
					for (InputIterator start = first; start != last; start++)
						n++;
				}

				if (size_ + n >= capacity_)
					resize(size_ + n + 1);
				for (size_type i = 0; i < n; i++)
				{
					allocator_.construct(&data_[size_ + i], value_type());
				}
				iterator start = end() + n - 1;
				iterator finish = end() - (pos);
				for (; start - (n - 1) != finish; start--)
				{
					allocator_.construct(&(*start), (*(start - n)));
					allocator_.destroy(&(*(start - n)));
				}
				for (size_type i = 0; i < n; i++, pos++, first++)
				{
					allocator_.construct(&data_[pos - 1], *first++);
				}
				size_ += n;
			}
		}

		size_type max_size() const throw()
		{
			// return (allocator_.max_size()); // why not?
			return (std::numeric_limits<size_type>::max() / std::max(2, static_cast<int>(sizeof(value_type))));
		}

		vector& operator=(const vector& x)
		{
			// modify size, not capacity
			size_type i;

			if (capacity_ < x.size_)
			{
				resize(x.size_);  // TODO: capacity에 x.capacity_를 넣을지 아니면 size_를 넣을 지 확인
			}

			for (i = 0; i < x.size_; i++)
			{
				/**
				 * value_type에서 operator=가 오버로딩 안되어있으면 ub
				 * https://m.cplusplus.com/reference/vector/vector/operator=/
				 */
				data_[i] = x.data_[i];
			}

			// TODO: optimization using checking is type trivial destructible
			if (!ft::is_trivial_destructible_junior<value_type>::value)
			{
				for (; i < size_; i++)
				{
					allocator_.destroy(&data_[i]);
				}
			}
			size_ = x.size_;
			return (*this);
		}

		reference operator[](size_type n)  // does not check bound
		{
			return (data_[n]);
		}
		const_reference operator[](size_type n) const
		{
			return (data_[n]);
		}

		void pop_back()
		{
			if (empty())
				return;
			// TODO: optimization using checking is type trivial destructible
			if (!ft::is_trivial_destructible_junior<value_type>::value)
				allocator_.destroy(&data_[size_ - 1]);
			size_--;
			if (size_ < (capacity_ / 4))
				resize(capacity_ / 2);
		}

		void push_back(const value_type& val) throw(std::bad_alloc)
		{
			if (size_ + 1 >= capacity_)
				resize(capacity_ * 2);
			data_[size_++] = val;
		}

		reverse_iterator rbegin() throw()
		{
			return (reverse_iterator(end()));
		}
		const_reverse_iterator rbegin() const throw()
		{
			return (const_reverse_iterator(end()));
		}

		reverse_iterator rend() throw()
		{
			return (reverse_iterator(begin()));
		}
		const_reverse_iterator rend() const throw()
		{
			return (const_reverse_iterator(begin()));
		}

		void reserve(size_type n) throw(std::length_error, std::bad_alloc)
		{
			if (capacity_ < n)
				resize(n);
		}

		void resize(size_type n, value_type val = value_type()) throw(std::bad_alloc)
		{
			pointer tmp;
			size_type i;

			// TODO: optimization using checking is type trivial destructible
			if (n > max_size())
				throw std::bad_alloc();
			if (size_ < n)
			{
				tmp = allocator_.allocate(sizeof(value_type) * n);
				if (!ft::is_trivial_destructible_junior<value_type>::value)
				{
					for (i = 0; i < size_; i++)
					{
						allocator_.construct(&tmp[i], data_[i]);
						allocator_.destroy(&data_[i]);
					}
				}
				else
				{
					for (i = 0; i < size_; i++)
						allocator_.construct(&tmp[i], data_[i]);
				}
				allocator_.deallocate(data_, capacity_);
				for (; i < n; i++)
				{
					allocator_.construct(&tmp[i], val);
				}
				data_ = tmp;
				capacity_ = n;
			}
		}
		size_type size() const throw()
		{
			return (size_);
		}

		void swap(vector& x)
		{
			pointer d = data_;
			data_ = x.data_;
			x.data_ = d;

			size_type n = size_;
			size_ = x.size_;
			x.size_ = n;

			size_type c = capacity_;
			capacity_ = x.capacity_;
			x.capacity_ = c;

			allocator_type tmp = get_allocator();
			allocator_ = x.get_allocator();
			x.allocator_ = tmp;
		}
	};
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), rhs.begin(), rhs.end()));
	}
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}
	template <class T, class Alloc>
	void swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
	{
		x.swap(y);
	}

	template <class Iterator, class Pointer>
	class vector_iterator
	{
	public:
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

		explicit vector_iterator(const Iterator& otherIter)
			: base_(otherIter) {}

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
		vector_iterator& operator--()
		{
			--base_;
			return (*this);
		}
		vector_iterator operator--(int)
		{
			vector_iterator tmp = *this;
			--(*this);
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
