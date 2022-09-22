/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:11:43 by tnaton            #+#    #+#             */
/*   Updated: 2022/09/22 20:50:20 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include "iterator.hpp"
# include <memory>
# include <iostream>

namespace ft {
	template <class T, class Allocator = std::allocator<T> > class Vector {
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
			Vector(){std::cout << "created a vector" << std::endl;};
//			explicit Vector(const Allocator& alloc){};
//			explicit Vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()){_lst = new value_type[count]; for (size_type i = 0; i < count; i++){_lst[i] = value;}};
//			explicit Vector(size_type count){_lst = new value_type[count]; for (size_type i = 0; i < count; i++){_lst[i] = Allocator::construct();}};
//			template <class InputIt> Vector(InputIt first, InputIt last, const Allocator& alloc = Allocator()){};
//			Vector(const Vector& other){this->_lst = other._lst;};
		private:
			pointer _lst;
	};
}

#endif
