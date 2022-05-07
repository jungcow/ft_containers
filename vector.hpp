#ifndef _VECTOR_H__
#define _VECTOR_H__

#include <exception>
#include <limits>
#include <memory>
#include <vector>

#include "iterator.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef Alloc allocator_type;
		typedef typename allocator_type::size_type size_type;

	public:
		typedef T value_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::difference_type difference_type;

		typedef __wrap_iter<pointer, vector> iterator;
		typedef __wrap_iter<const_pointer, vector> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	protected:
		pointer _data;
		pointer _begin;
		pointer _end;
		size_type _capacity;
		size_type _size;
		allocator_type _allocator;

	public:
		/*
		** Constructor
		*/
		explicit vector(const allocator_type &alloc = allocator_type())
			: _capacity(1), _size(0), _begin(NULL), _end(NULL), _allocator(alloc)
		{
			std::cout << "vector default constructor\n";
			_data = NULL;
		};

		explicit vector(size_type n, const value_type &v = value_type(),
						const allocator_type &alloc = allocator_type())
			: _capacity(n), _size(n), _allocator(alloc)
		{
			std::cout << "vector size constructor\n";

			// TODO: 이 생성자는 속도를 높이기 위해 첫 번째 요소만 생성한 후 나머지 n-1개의 요소는 복사 생성자를 호출하여 생성한다.
			_data = _allocator.allocate((sizeof(value_type) * n));
			for (size_type i = 0; i < _size; i++) {
				_allocator.construct(&_data[i], v);
			}
			_begin = &_data[0];
			_end = &_data[n];  // TODO: allocator에 의해 n보다 더 큰게 할당되서 가능한건가?
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last,
			   const allocator_type &alloc = allocator_type(),
			   typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = nullptr)
			: _size(), _capacity(1), _allocator(alloc)
		{
			// TODO: Forward와 input iterator를 구분하여 forward일 때 최적화를 시켜주도록 하자.
			/**
			 * forward iterator일 땐, begin과 end에 단순히 대입하는 것으로?? 한번에??
			 */
			std::cout << "vector iterator constructor\n";

			typename iterator::difference_type d = last - first;
			_size = d;
			_capacity = d;
			_data = _allocator.allocate(sizeof(value_type) * d);

			for (size_type i = 0; first != last; first++, i++) {
				_allocator.construct(&_data[i], *first);
			}
			_begin = &_data[0];
			_end = &_data[_size];
			// ft::iterator_traits<iterator>::differency_type d = last - first;
			// _data = _allocator.allocate((sizeof(value_type) * d));
			// memcpy()
		}

		vector(const vector &other) : _allocator(get_allocator())
		{
			_data = _allocator.allocate(sizeof(value_type) * _size);
			*this = other;
		}

		vector &operator=(const vector &other)
		{
			for (size_type i = 0; i < other._size; i++) {
				_allocator.destroy(&_data[i]);
			}
			reserve(other._capacity);
			for (size_type i = 0; i < other._size; i++) {
				_allocator.construct(&_data[i], other[i]);
				std::cout << other[i] << std::endl;
			}
			this->_size = other._size;
			return *this;
		}

		virtual ~vector()
		{
			std::cout << "vector destructor" << std::endl;
			for (size_type i = 0; i < _size; i++) {
				_allocator.destroy(&_data[i]);
			}
			_allocator.deallocate(_data, _capacity);
		}

		reference operator[](size_type n)
		{
			return _data[n];
		}
		const_reference operator[](size_type n) const
		{
			return _data[n];
		}
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
		{
			typename ft::iterator_traits<InputIterator>::difference_type distance = last - first;
			if (distance > _capacity) {
				reserve(distance);
			}
			for (size_type i = 0; i < distance; i++) {
				_allocator.destroy(&_data[i]);
			}
			for (size_type i = 0; i < distance && first != end; i++, first++) {
				_allocator.construct(&_data[i], *first);
			}
			_size = distance;
		}

		void assign(size_type n, const value_type &val)
		{
			if (n > max_size()) {
				throw std::length_error("assign: Exceed on max size");
			}
			if (n > _capacity) {
				reserve(n);
			}
			for (size_type i = 0; i < n; i++) {
				_allocator.destroy(&_data[i]);
			}
			for (size_type i = 0; i < n; i++) {
				_allocator.construct(&_data[i], val);
			}
			_size = n;
		}
		reference at(size_type n) throw(std::out_of_range)
		{
			if (n + 1 > _size) {
				throw std::out_of_range("at: Out of bounds");
			}
			return _data[n];
		}
		const_reference at(size_type n) const throw(std::out_of_range)
		{
			if (n + 1 > _size) {
				throw std::out_of_range("at: Out of bounds");
			}
			return _data[n];
		}

		void clear() throw()
		{
			_size = 0;
		}

		iterator erase(iterator position)
		{
			for (; (position + 1) != end(); position++) {
				*position = *(position + 1);
			}
			_allocator.destroy(&(*position));
			_size -= 1;
		}
		iterator erase(iterator first, iterator last)
		{
			typename iterator::difference_type distance = last - first;
			for (; first != last; first++) {
				if (first + distance != end()) {
					*first = *(first + distance);
				}
			}
			for (; last != end(); last++) {
				_allocator.destroy(&(*last));
			}
			_size -= distance;
		}
		iterator insert(iterator position, const value_type &val)
		{
			iterator last;
			for (; last != position; last--) {
				*last = *(last - 1);
			}
		}
		void insert(iterator position, size_type n, const value_type &val);
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);

		void reserve(size_type n) throw(std::length_error)
		{
			if (n > max_size())
				throw std::length_error("reserve: Exceed on max size");
			if (n > _capacity) {
				for (size_type i = 0; i < _size; i++) {
					_allocator.destroy(&_data[i]);
				}
				_allocator.deallocate(_data, _capacity);
				_data = _allocator.allocate(sizeof(value_type) * n);
				_capacity = n;
			}
		}

		size_type max_size(void) throw()
		{
			return _allocator.max_size();
		}

		size_type capacity() const throw()
		{
			return _capacity;
		}
		size_type size() const throw()
		{
			return _size;
		}

		bool empty() const throw()
		{
			return _size == 0;
		}

		reference front() throw()
		{
			return _data[0];
		}
		const_reference front() const throw()
		{
			return _data[0];
		}
		reference back() throw()
		{
			return _data[_size - 1];
		}
		const_reference back() const throw()
		{
			return _data[_size - 1];
		}

		iterator begin() throw()
		{
			return iterator(_begin);
		}
		const_iterator begin() const throw()
		{
			return iterator(_begin);
		}

		iterator end() throw()
		{
			return iterator(_end);
		}
		const_iterator end() const throw()
		{
			return iterator(_end);
		}

		allocator_type get_allocator(void) const throw()
		{
			return this->allocator;
		};
	};
};
#endif