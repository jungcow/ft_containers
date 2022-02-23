#ifndef _VECTOR_H__
#define _VECTOR_H__

#include <cmath>
#include <memory>

#include "iterator.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef Alloc										allocator_type;
		typedef typename allocator_type::size_type			size_type;

	protected:
		T * 		_data;
		size_type	_capacity;
		size_type	_size;

	public:
		typedef T											value_type;
		typedef value_type &								reference;
		typedef const value_type &							const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::difference_type	difference_type;

		typedef __wrap_iter<pointer, ft::vector<value_type> > 			iterator;
		typedef __wrap_iter<const_pointer, ft::vector<value_type> >		const_iterator;
		// typedef reverse_iterator<iterator>					reverse_iterator;
		// typedef reverse_iterator<const_iterator>			const_reverse_iterator;
		/*
		** Constructor
		*/
		explicit vector(const allocator_type &alloc = allocator_type()) {};
			// : _capacity(0), _size(0) {}

		// explicit vector(size_type n, const value_type &v = value_type(),
		// 				const allocator_type &alloc = allocator_type())
		// {
		// 	_size = n;

		// 	int tmp = std::ceil(std::log(n) / std::log(2));
		// 	_capacity = tmp * tmp;
		// }

		// template <class InputIterator>
		// vector(InputIterator first, InputIterator last,
		// 	   const allocator_type &alloc = allocator_type())
		// 	: _size(0), _capacity(0)
		// {
		// 	typename vector<value_type>::iterator vi;

		// 	for (typename vector<value_type>::iterator vi = first; vi != last; vi++)
		// 		_size++;
		// }

		// vector(const vector &x) { *this = x; }

		// vector &operator=(const vector &rfs)
		// {
		// 	std::cout << "assignment operator" << std::endl;
		// 	// 동적 배열 순회
		// }

		virtual ~vector() {}
	};
};
#endif