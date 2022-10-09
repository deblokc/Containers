/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:11:29 by tnaton            #+#    #+#             */
/*   Updated: 2022/10/09 17:22:15 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <iterator>
# include "iterator_traits.hpp"

namespace ft {
	template <class T, class Category = std::random_access_iterator_tag, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&> class Iterator {
		public:
			typedef Category	iterator_category;
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;

			Iterator(void){}
			Iterator(const Iterator & other){this->_ptr = other._ptr;}
			Iterator(pointer ptr){this->_ptr = ptr;}
			~Iterator(void){}

			Iterator &operator=(const Iterator & other){if (this != &other){this->_ptr = other._ptr;}return *this;}
			Iterator &operator++(void){this->_ptr++;return *this;}
			Iterator operator++(int){Iterator tmp(*this);this->_ptr++;return tmp;}
			Iterator &operator--(void){this->_ptr--;return *this;}
			Iterator operator--(int){Iterator tmp(*this);this->_ptr--;return tmp;}

			value_type &operator[](difference_type n){return (*(this->_ptr + n));}
			value_type &operator*(void){return *(this->_ptr);}
			value_type *operator->(void){return this->_ptr;}

			Iterator &operator+=(difference_type n){this->_ptr += n; return *this;}
			Iterator &operator-=(difference_type n){this->_ptr -= n; return *this;}
			Iterator operator+(difference_type n){Iterator tmp(*this); tmp += n; return (tmp);}
			Iterator operator-(difference_type n){Iterator tmp(*this); tmp -= n; return (tmp);}

			difference_type operator-(const Iterator & other){return (_ptr - other._ptr);}

			bool operator==(const Iterator & other){return this->_ptr == other._ptr;}
			bool operator!=(const Iterator & other){return this->_ptr != other._ptr;}
			bool operator>(const Iterator & other){return this->_ptr > other._ptr;}
			bool operator>=(const Iterator & other){return this->_ptr >= other._ptr;}
			bool operator<(const Iterator & other){return this->_ptr < other._ptr;}
			bool operator<=(const Iterator & other){return this->_ptr <= other._ptr;}

			friend Iterator operator+(typename Iterator::difference_type n, Iterator i){return (i + n);}
			friend Iterator operator-(typename Iterator::difference_type n, Iterator i){return (i - n);}
		private:
			pointer _ptr;
	};
}
#endif
