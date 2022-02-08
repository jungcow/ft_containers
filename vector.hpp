#ifndef _VECTOR_H__
#define _VECTOR_H__

#include <cmath>
#include <memory>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector;
};

template <class T, class Alloc = std::allocator<T> >
class vector
{
private:
	size_t _capacity;
	size_t _size;

public:
	typedef Alloc allocator_type;
	typedef typename allocator_type::size_type size_type;

protected:
	typedef T value_type;
	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef typename allocator_type::difference_type difference_type;

	typedef pointer iterator;
	typedef const_pointer const_iterator;

public:
	/*
	** Constructor
	*/
	explicit vector(const allocator_type &alloc = allocator_type())
		: _capacity(0), _size(0) {}

	explicit vector(size_type n, const value_type &v = value_type(), const allocator_type &alloc = allocator_type())
	{
		_size = n;
		_capacity = std::pow(2.0, std::ceil(log(n) / log(2)));
	}

	template <class InputIterator>
	vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type())
	{
		const vector<value_type>::iterator vi;

		for (_size = 0, const vector<value_type>::iterator vi = first; vi != last; vi++)
			_size++;
	}

	vector(const vector &x);

	virtual ~vector();
};

#endif