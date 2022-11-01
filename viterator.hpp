/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viterator.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:03:46 by tnaton            #+#    #+#             */
/*   Updated: 2022/10/31 17:46:53 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"
#include "utils.hpp"

namespace ft {
	template <typename ptr, typename ctnr>
	class viterator {
		public :
			typedef	ptr													iterator_type;
			typedef typename iterator_traits<ptr>::iterator_category	iterator_category;
			typedef typename iterator_traits<ptr>::value_type			value_type;
			typedef typename iterator_traits<ptr>::difference_type		difference_type;
			typedef typename iterator_traits<ptr>::reference			reference;
			typedef typename iterator_traits<ptr>::pointer				pointer;

			viterator() : _ptr(iterator_type()) {}
			explicit viterator(const iterator_type & other_ptr) : _ptr(other_ptr) {}

			template <typename Ptr>
			viterator(const viterator<Ptr, typename enable_if<is_same<Ptr, typename ctnr::pointer>::value, ctnr>::type> & other) : _ptr(other.base()) {}

			~viterator() {}

			viterator & operator=(const viterator &other) {
			//	if (*this == &other)
			//		return (*this);
				this->_ptr = other._ptr;
				return (*this);
			}

			const iterator_type & base(void) const {return _ptr;}
			reference operator*(void) const {return *_ptr;}
			pointer operator->(void) const {return _ptr;}
			reference operator[](difference_type n) {return *(_ptr + n);}

			viterator & operator++(void) {this->_ptr++; return *this;}
			viterator operator++(int) {return viterator(this->_ptr++);}
			viterator & operator--(void) {this->_ptr--; return *this;}
			viterator operator--(int) {return viterator(this->_ptr--);}

			viterator & operator+=(difference_type n){this->_ptr += n; return *this;}
			viterator & operator-=(difference_type n){this->_ptr -= n; return *this;}
			viterator operator+(difference_type n) const {return viterator(this->_ptr + n);}
			viterator operator-(difference_type n) const {return viterator(this->_ptr - n);}

		protected :
			iterator_type _ptr;
	};

	template <typename lit, typename rit, typename ctnr>
	bool operator==(const viterator<lit, ctnr> & lhs, const viterator<rit, ctnr> & rhs) {
		return (lhs.base() == rhs.base());
	}

	template <typename it, typename ctnr>
	bool operator==(const viterator<it, ctnr> & lhs, const viterator<it, ctnr> & rhs) {
		return (lhs.base() == rhs.base());
	}

	template <typename lit, typename rit, typename ctnr>
	bool operator!=(const viterator<lit, ctnr> & lhs, const viterator<rit, ctnr> & rhs) {
		return (lhs.base() != rhs.base());
	}

	template <typename it, typename ctnr>
	bool operator!=(const viterator<it, ctnr> & lhs, const viterator<it, ctnr> & rhs) {
		return (lhs.base() != rhs.base());
	}

	template <typename lit, typename rit, typename ctnr>
	bool operator<(const viterator<lit, ctnr> & lhs, const viterator<rit, ctnr> & rhs) {
		return (lhs.base() < rhs.base());
	}

	template <typename it, typename ctnr>
	bool operator<(const viterator<it, ctnr> & lhs, const viterator<it, ctnr> & rhs) {
		return (lhs.base() < rhs.base());
	}

	template <typename lit, typename rit, typename ctnr>
	bool operator<=(const viterator<lit, ctnr> & lhs, const viterator<rit, ctnr> & rhs) {
		return (lhs.base() <= rhs.base());
	}

	template <typename it, typename ctnr>
	bool operator<=(const viterator<it, ctnr> & lhs, const viterator<it, ctnr> & rhs) {
		return (lhs.base() <= rhs.base());
	}

	template <typename lit, typename rit, typename ctnr>
	bool operator>(const viterator<lit, ctnr> & lhs, const viterator<rit, ctnr> & rhs) {
		return (lhs.base() > rhs.base());
	}

	template <typename it, typename ctnr>
	bool operator>(const viterator<it, ctnr> & lhs, const viterator<it, ctnr> & rhs) {
		return (lhs.base() > rhs.base());
	}

	template <typename lit, typename rit, typename ctnr>
	bool operator>=(const viterator<lit, ctnr> & lhs, const viterator<rit, ctnr> & rhs) {
		return (lhs.base() >= rhs.base());
	}

	template <typename it, typename ctnr>
	bool operator>=(const viterator<it, ctnr> & lhs, const viterator<it, ctnr> & rhs) {
		return (lhs.base() >= rhs.base());
	}

	template <typename lit, typename rit, typename ctnr>
	typename viterator<lit, ctnr>::difference_type operator-(const viterator<lit, ctnr> & lhs, const viterator<rit, ctnr> & rhs) {
		return (lhs.base() - rhs.base());
	}

	template <typename it, typename ctnr>
	typename viterator<it, ctnr>::difference_type operator-(const viterator<it, ctnr> & lhs, const viterator<it, ctnr> & rhs) {
		return (lhs.base() - rhs.base());
	}

	template <typename it, typename ctnr>
	viterator<it, ctnr> operator+(typename viterator<it, ctnr>::difference_type n, const viterator<it, ctnr> & iter) {
		return viterator<it, ctnr>(iter.base() + n);
	}

}
