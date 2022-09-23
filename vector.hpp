/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:11:43 by tnaton            #+#    #+#             */
/*   Updated: 2022/09/23 12:43:46 by tnaton           ###   ########.fr       */
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
				_lst = NULL;
				_start = NULL;
				_end = NULL;
				_cap_end = NULL;
				std::cout << "vector default/alloc constructor" << std::endl;
			};
//			explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()){_lst = new value_type[count]; for (size_type i = 0; i < count; i++){_lst[i] = value;}};
//			explicit vector(size_type count){_lst = new value_type[count]; for (size_type i = 0; i < count; i++){_lst[i] = Allocator::construct();}};
//			template <class InputIt> vector(InputIt first, InputIt last, const Allocator& alloc = Allocator()){};
			vector(const vector& other){this->_lst = other._lst;std::cout << "vector copy constructor" << std::endl;};
		private:
			pointer			_lst;
			pointer			_start;
			pointer			_end;
			pointer			_cap_end;
			allocator_type	_alloc;
	};
}

#endif
