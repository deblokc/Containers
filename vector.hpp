#ifndef VECTOR_HPP
# define VECTOR_HPP
# include "iterator.hpp"
#ifndef

namespace ft {
	template <class T, class Allocator = std::allocator<T> > class Vector {
		public:
			typedef T									value_type;
			typedef Allocator							allocator_type;
			typedef size_t								size_type;
			typedef ptrdiff_t							difference_type;
			typename typedef Allocator::reference		reference;
			typename typedef Allocator::const_reference	const_reference;
			typename typedef Allocator::pointer			pointer;
			typename typedef Allocator::const_pointer	const_pointer;
			typename typedef Iterator<T>				iterator;
	};
}
