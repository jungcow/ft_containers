#ifndef __FT_MAP_H__
#define __FT_MAP_H__

#include <functional>  // std::less

#include "utility.hpp"

template <class Key,
		  class T,
		  class Compare = std::less<Key>,
		  class Alloc = std::allocator<ft::pair<const Key, T> > >
class map
{
};

#endif