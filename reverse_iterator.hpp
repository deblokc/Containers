/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 19:00:11 by tnaton            #+#    #+#             */
/*   Updated: 2022/11/22 19:00:53 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP
# include <iterator>
# include "viterator.hpp"
#include <iostream>

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

			reverse_iterator(void): _it(){}
			reverse_iterator(const reverse_iterator & other){this->_it = other._it;}
			explicit reverse_iterator(Iter it): _it(it){}

			template <typename It>
			reverse_iterator(const reverse_iterator<It> & other): _it(other.base()) {}

			~reverse_iterator(void){}

			reverse_iterator & operator=(const reverse_iterator & other){if (this != &other){this->_it = other._it;}return *this;}
			reverse_iterator & operator++(void){this->_it--;return *this;}
			reverse_iterator operator++(int){reverse_iterator tmp(*this);this->_it--;return tmp;}
			reverse_iterator & operator--(void){this->_it++;return *this;}
			reverse_iterator operator--(int){reverse_iterator tmp(*this);this->_it++;return tmp;}

			Iter		base(void) const {return (_it);}
			reference operator[](difference_type n) const {return *(*this + n);}
			reference operator*(void) const {Iter tmp = _it; return (*--tmp);}
			pointer operator->(void) const {return &(operator*());}

			reverse_iterator operator+(difference_type n) const {return reverse_iterator(base() - n);}
			reverse_iterator operator-(difference_type n) const {return reverse_iterator(base() + n);}
			reverse_iterator & operator+=(difference_type n){this->_it -= n; return *this;}
			reverse_iterator & operator-=(difference_type n){this->_it += n; return *this;}

		private:
			Iter _it;
	};

	template<class Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& rit) {
		return (reverse_iterator<Iter>(rit.base() - n));
	}

	template<class Iter>
	typename reverse_iterator<Iter>::difference_type operator-(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) {
		return (rhs.base() - lhs.base());
	}

	template<class Lit, class Rit>
	typename reverse_iterator<Lit>::difference_type operator-(const reverse_iterator<Lit>& lhs, const reverse_iterator<Rit>& rhs) {
		return (rhs.base() - lhs.base());
	}

	template<class Iterator1, class Iterator2>
	bool operator==(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() == rhs.base());
	}

	template<class Iterator1, class Iterator2>
	bool operator!=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {
		return !(lhs == rhs);
	}

	template<class Iterator1, class Iterator2>
	bool operator<(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {
		return (rhs.base() < lhs.base());
	}

	template<class Iterator1, class Iterator2>
	bool operator<=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {
		return !(rhs < lhs);
	}

	template<class Iterator1, class Iterator2>
	bool operator>(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {
		return (rhs < lhs);
	}

	template<class Iterator1, class Iterator2>
	bool operator>=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {
		return !(lhs < rhs);
	}

}

#endif
