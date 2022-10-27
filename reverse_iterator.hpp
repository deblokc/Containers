/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 19:00:11 by tnaton            #+#    #+#             */
/*   Updated: 2022/10/27 19:44:57 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP
# include <iterator>
# include "iterator.hpp"

namespace ft {
	template <class Iter>
	class reverse_iterator {
		public:
			typedef iterator_traits<Iter>								iterator;
			typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iter>::value_type			value_type;
			typedef typename iterator_traits<Iter>::difference_type		difference_type;
			typedef typename iterator_traits<Iter>::pointer				pointer;
			typedef typename iterator_traits<Iter>::reference			reference;

			reverse_iterator(void){}
			reverse_iterator(const reverse_iterator & other){this->_it = other._it;}
			reverse_iterator(iterator it){this->_it = it;}
			~reverse_iterator(void){}

			reverse_iterator &operator=(const reverse_iterator & other){if (this != &other){this->_it = other._it;}return *this;}
			reverse_iterator &operator++(void){this->_it--;return *this;}
			reverse_iterator operator++(int){reverse_iterator tmp(*this);this->_it--;return tmp;}
			reverse_iterator &operator--(void){this->_it++;return *this;}
			reverse_iterator operator--(int){reverse_iterator tmp(*this);this->_it++;return tmp;}

			value_type &operator[](difference_type n){return (*(this->_it - n));}
			value_type &operator*(void){return *(this->_it);}
			value_type *operator->(void){return this->_it;}

			reverse_iterator &operator+=(difference_type n){this->_it -= n; return *this;}
			reverse_iterator &operator-=(difference_type n){this->_it += n; return *this;}
			reverse_iterator operator+(difference_type n){reverse_iterator tmp(*this); tmp -= n; return (tmp);}
			reverse_iterator operator-(difference_type n){reverse_iterator tmp(*this); tmp += n; return (tmp);}

			difference_type operator-(const reverse_iterator & other){return (_it + other._it);}
			difference_type operator+(const reverse_iterator & other){return (_it - other._it);}

			bool operator==(const reverse_iterator & other){return this->_it == other._it;}
			bool operator!=(const reverse_iterator & other){return this->_it != other._it;}
			bool operator>(const reverse_iterator & other){return this->_it > other._it;}
			bool operator>=(const reverse_iterator & other){return this->_it >= other._it;}
			bool operator<(const reverse_iterator & other){return this->_it < other._it;}
			bool operator<=(const reverse_iterator & other){return this->_it <= other._it;}
			
			friend reverse_iterator operator+(typename reverse_iterator::difference_type n, reverse_iterator i){return (i + n);}
			friend reverse_iterator operator-(typename reverse_iterator::difference_type n, reverse_iterator i){return (i - n);}

		private:
			iterator _it;
	};
}

#endif
