#ifndef _VECTOR_H__
#define _VECTOR_H__

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

	public:
		/*
		** Constructor
		*/
		explicit vector(const allocator_type &alloc = allocator_type())
			: _capacity(1), _size(0), _begin(NULL), _end(NULL)
		{
			std::cout << "vector default constructor\n";
			_data = NULL;
		};

		explicit vector(size_type n, const value_type &v = value_type(),
						const allocator_type &alloc = allocator_type())
			: _capacity(n), _size(n)
		{
			std::cout << "vector size constructor\n";

			// TODO: 이 생성자는 속도를 높이기 위해 첫 번째 요소만 생성한 후 나머지 n-1개의 요소는 복사 생성자를 호출하여 생성한다.
			std::allocator<T> allocator = get_allocator();
			_data = allocator.allocate((sizeof(value_type) * n));
			allocator.construct(_data, v);
			_begin = &_data[0];
			_end = &_data[n];  // TODO: allocator에 의해 n보다 더 큰게 할당되서 가능한건가?
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last,
			   const allocator_type &alloc = allocator_type(),
			   typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = nullptr)
			: _size(), _capacity(1)
		{
			// TODO: Forward와 input iterator를 구분하여 forward일 때 최적화를 시켜주도록 하자.
			/**
			 * forward iterator일 땐, begin과 end에 단순히 대입하는 것으로?? 한번에??
			 */
			std::cout << "vector iterator constructor\n";

			typename iterator::difference_type d = last - first;
			_size = d;
			_capacity = d;
			_data = get_allocator().allocate(sizeof(value_type) * d);

			for (size_type i = 0; first != last; first++, i++) {
				get_allocator().construct(&_data[i], *first);
			}
			_begin = &_data[0];
			_end = &_data[_size];
			// ft::iterator_traits<iterator>::differency_type d = last - first;
			// _data = get_allocator().allocate((sizeof(value_type) * d));
			// memcpy()
		}

		// vector(const vector &x) { *this = x; }

		virtual ~vector()
		{
			std::cout << "vector destructor" << std::endl;
			get_allocator().destroy(_data);
			get_allocator().deallocate(_data, _capacity);
		}

		size_type capacity() const throw() {
			return _capacity;
		}

		bool empty() const throw() {
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
			return allocator_type();
		};
	};
};
#endif