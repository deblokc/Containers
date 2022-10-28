/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 19:00:11 by tnaton            #+#    #+#             */
/*   Updated: 2022/10/29 00:05:55 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP
# include <iterator>
# include "iterator.hpp"
#include <iostream>

namespace ft {
	template <class Iter>
	class reverse_iterator : public std::iterator<typename iterator_traits<Iter>::iterator_category, typename iterator_traits<Iter>::value_type, typename iterator_traits<Iter>::difference_type, typename iterator_traits<Iter>::pointer, typename iterator_traits<Iter>::reference> {
		public:
			typedef iterator_traits<Iter>								iterator;
			typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iter>::value_type			value_type;
			typedef typename iterator_traits<Iter>::difference_type		difference_type;
			typedef typename iterator_traits<Iter>::pointer				pointer;
			typedef typename iterator_traits<Iter>::reference			reference;

			reverse_iterator(void): _it(){}
			reverse_iterator(const reverse_iterator & other){this->_it = other._it;}
			reverse_iterator(Iter it): _it(it){}
			~reverse_iterator(void){}

			reverse_iterator &operator=(const reverse_iterator & other){if (this != &other){this->_it = other._it;}return *this;}
			reverse_iterator &operator++(void){this->_it--;return *this;}
			reverse_iterator operator++(int){reverse_iterator tmp(*this);this->_it--;return tmp;}
			reverse_iterator &operator--(void){this->_it++;return *this;}
			reverse_iterator operator--(int){reverse_iterator tmp(*this);this->_it++;return tmp;}

			Iter		base(void) const {return (_it - 1);}
			value_type &operator[](difference_type n){return (*(this->_it - n - 1));}
			value_type &operator*(void){return *(this->_it - 1);}
			value_type *operator->(void){return (&(*(this->_it - 1)));}

			reverse_iterator &operator+=(difference_type n){this->_it -= n; return *this;}
			reverse_iterator &operator-=(difference_type n){this->_it += n; return *this;}
			reverse_iterator operator+(difference_type n){reverse_iterator tmp(*this); tmp += n; return (tmp);}
			reverse_iterator operator-(difference_type n){reverse_iterator tmp(*this); tmp -= n; return (tmp);}

			difference_type operator-(const reverse_iterator & other) {return -(_it - other._it);}

		public:
			bool operator==(const reverse_iterator & other){return this->_it == other._it;}
			bool operator!=(const reverse_iterator & other){return this->_it != other._it;}
			bool operator>(const reverse_iterator & other){return this->_it > other._it;}
			bool operator>=(const reverse_iterator & other){return this->_it >= other._it;}
			bool operator<(const reverse_iterator & other){return this->_it < other._it;}
			bool operator<=(const reverse_iterator & other){return this->_it <= other._it;}
			
			friend reverse_iterator operator+(typename reverse_iterator::difference_type n, reverse_iterator i){return (i + n);}
			friend reverse_iterator operator-(typename reverse_iterator::difference_type n, reverse_iterator i){return (i - n);}

		private:
			Iter _it;
	};
}

#endif
