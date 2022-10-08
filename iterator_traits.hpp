/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:11:34 by tnaton            #+#    #+#             */
/*   Updated: 2022/09/22 17:48:42 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP
# include <iterator>

namespace ft {

	struct random_access_iterator_tag {};

	struct bidirectional_iterator_tag {};

	struct forward_iterator_tag {};

	struct input_iterator_tag {};

	struct output_iterator_tag {};

	template<class Iter> struct iterator_traits {
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template<class T> struct iterator_traits<T*> {
		typedef ptrdiff_t									difference_type;
		typedef T											value_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef typename ft::random_access_iterator_tag		iterator_category;
	};

	template<class T> struct iterator_traits<const T*> {
		typedef ptrdiff_t									difference_type;
		typedef T											value_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef typename ft::random_access_iterator_tag		iterator_category;
	};

	template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
		class iterator {
			typedef Distance	difference_type;
			typedef T			value_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
			typedef Category	iterator_category;
		};

	template<class T>
		class InputIterator : ft::iterator<ft::input_iterator_tag, T> {
			typedef typename ft::iterator<ft::input_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::input_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::input_iterator_tag, T>::pointer			pointer;
			typedef typename ft::iterator<ft::input_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<ft::input_iterator_tag, T>::iterator_category	iterator_category;

			InputIterator(pointer ptr): _ptr(ptr) {}

			InputIterator(const InputIterator & other): _ptr(other._ptr) {}

			reference	operator*(void) const {
				return (*_ptr);
			}

			pointer		operator->(void) const {
				return (_ptr);
			}

			reference	operator++(void) {
				_ptr++;
				return (*this);
			}

			InputIterator	operator++(int) {
				InputIterator tmp(*this);
				_ptr++;
				return tmp;
			}

			protected:
				pointer	_ptr;
		};
}
#endif

