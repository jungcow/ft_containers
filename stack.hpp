#ifndef __FT_STACK_H__
#define __FT_STACK_H__

#include "vector.hpp"

template <class T, class Container = ft::vector<T> >
class stack
{
private:
	typedef T value_type;
	typedef Container container_type;
	typedef typename Container::size_type size_type;
};

#endif
