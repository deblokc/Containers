/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:11:43 by tnaton            #+#    #+#             */
/*   Updated: 2022/09/23 17:56:20 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include "iterator.hpp"
# include <memory>
# include <iostream>

namespace ft {
	template <class T, class Allocator = std::allocator<T> > class vector {
		public:
			typedef T									value_type;
			typedef Allocator							allocator_type;
			typedef size_t								size_type;
			typedef std::ptrdiff_t						difference_type;
			typedef typename Allocator::reference		reference;
			typedef typename Allocator::const_reference	const_reference;
			typedef typename Allocator::pointer			pointer;
			typedef typename Allocator::const_pointer	const_pointer;
			typedef typename ft::Iterator<T>			iterator;

		public:
			explicit vector(const allocator_type& alloc = allocator_type()){
				_alloc = alloc;
				_start = NULL;
				_end = NULL;
				_cap_end = NULL;
				_size = 0;
				std::cout << "vector default/alloc constructor" << std::endl;
			};

			explicit vector(size_type count, const value_type& value = value_type(), \
					const allocator_type& alloc = Allocator()) {
				_alloc = alloc;
				_start = NULL;
				_end = NULL;
				_cap_end = NULL;
				_size = count;
				_start = _alloc.allocate(count);
				_end = _start;
				for (size_type i = 0; i < count; i++){
					_alloc.construct(_end, value);
					_end++;
				}
				_cap_end = _start + count;
				std::cout << "vector xval constructor" << std::endl;
			};

			template <class InputIt> vector(InputIt first, InputIt last, \
					const Allocator& alloc = Allocator()){
				InputIt tmp = first;
				_size = 0;
				while (tmp != last){
					tmp++;
					_size++;
				}
				_alloc = alloc;
				_start = _alloc.allocate(_size);
				_end = _start;
				while (first != last) {
					_alloc.construct(_end, first);
					first++;
					_end++;
				}
				_cap_end = _start + _size;
				std::cout << "vector input constructor" << std::endl;
			};

			vector(const vector& other){
				_alloc = other._alloc;
				_start = other._start;
				_end = other._end;
				_cap_end = other._end;
				_size = other._size;
				std::cout << "vector copy constructor" << std::endl;
			};

			~vector(void){
				if (_size)
					_alloc.deallocate(_start, _size);
				std::cout << "vector destructor" << std::endl;
			};

		private:
			pointer			_start;
			pointer			_end;
			pointer			_cap_end;
			allocator_type	_alloc;
			size_type		_size;
	};
}

#endif
