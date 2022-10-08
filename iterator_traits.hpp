/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:11:34 by tnaton            #+#    #+#             */
/*   Updated: 2022/10/08 20:25:23 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP
# include <iterator>

namespace ft {

	template<class Iter> struct iterator_traits {
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template<class T> struct iterator_traits<T*> {
		typedef std::ptrdiff_t								difference_type;
		typedef T											value_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef typename std::random_access_iterator_tag	iterator_category;
	};
/*
	template<class T> struct iterator_traits<const T*> {
		typedef std::ptrdiff_t									difference_type;
		typedef T											value_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef typename ft::random_access_iterator_tag		iterator_category;
	};
*/
	template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
		class iterator {
			typedef Distance	difference_type;
			typedef T			value_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
			typedef Category	iterator_category;
		};

/*
	template<class T>
		class InputIterator : ft::iterator<ft::input_iterator_tag, T> {
			typedef typename ft::iterator<ft::input_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::input_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::input_iterator_tag, T>::pointer			pointer;
			typedef typename ft::iterator<ft::input_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<ft::input_iterator_tag, T>::iterator_category	iterator_category;

			InputIterator(pointer ptr): _ptr(ptr) {}

			InputIterator(const InputIterator & other): _ptr(other._ptr) {}

			InputIterator	operator=(const InputIterator & other) {
				if (this == &other)
					return (*this);
				_ptr = other._ptr;
				return (*this);
			}

			~InputIterator(void) {}

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

			bool operator==(const InputIterator & other) {
				return (_ptr == other._ptr);
			}

			bool operator!=(const InputIterator & other) {
				return (_ptr != other._ptr);
			}

			protected:
				pointer	_ptr;
		};

	template<class T>
		class OutputIterator : ft::iterator<ft::output_iterator_tag, T> {
			typedef typename ft::iterator<ft::output_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<ft::output_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<ft::output_iterator_tag, T>::pointer				pointer;
			typedef typename ft::iterator<ft::output_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<ft::output_iterator_tag, T>::iterator_category	iterator_category;

			OutputIterator(pointer ptr): _ptr(ptr) {}

			OutputIterator(const OutputIterator & other): _ptr(other._ptr) {}

			OutputIterator	operator=(const OutputIterator & other) {
				if (this == &other)
					return (*this);
				_ptr = other._ptr;
				return (*this);
			}

			~OutputIterator(void) {}

			reference	operator*(void) {
				return (*_ptr);
			}

			reference	operator++(void) {
				_ptr++;
				return (*this);
			}

			OutputIterator	operator++(int) {
				OutputIterator tmp(*this);
				_ptr++;
				return (tmp);
			}

			protected:
				pointer	_ptr;
		};

	template<class T>
		class ForwardIterator : ft::iterator<ft::forward_iterator_tag, T> {
			typedef typename ft::iterator<ft::forward_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<ft::forward_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<ft::forward_iterator_tag, T>::pointer				pointer;
			typedef typename ft::iterator<ft::forward_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<ft::forward_iterator_tag, T>::iterator_category	iterator_category;

			ForwardIterator(void): _ptr(NULL) {}

			ForwardIterator(pointer ptr): _ptr(ptr) {}

			ForwardIterator(const ForwardIterator & other): _ptr(other._ptr) {}

			ForwardIterator	operator=(const ForwardIterator & other) {
				if (this == &other)
					return (*this);
				_ptr = other._ptr;
				return (*this);
			}

			~ForwardIterator(void) {}

			reference	operator*(void) {
				return (*_ptr);
			}

			reference	operator++(void) {
				_ptr++;
				return (*this);
			}

			ForwardIterator	operator++(int) {
				ForwardIterator tmp(*this);
				_ptr++;
				return (tmp);
			}

			bool operator==(const ForwardIterator & other) {
				return (_ptr == other._ptr);
			}

			bool operator!=(const ForwardIterator & other) {
				return (_ptr != other._ptr);
			}

			protected:
				pointer	_ptr;

		};

	template<class T>
		class BidirectionalIterator : ft::iterator<ft::bidirectional_iterator_tag, T> {
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer				pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;

			BidirectionalIterator(void): _ptr(NULL) {}

			BidirectionalIterator(pointer ptr): _ptr(ptr) {}

			BidirectionalIterator(const BidirectionalIterator & other): _ptr(other._ptr) {}

			BidirectionalIterator	operator=(const BidirectionalIterator & other) {
				if (this == &other)
					return (*this);
				_ptr = other._ptr;
				return (*this);
			}

			~BidirectionalIterator(void) {}

			reference	operator*(void) {
				return (*_ptr);
			}

			reference	operator++(void) {
				_ptr++;
				return (*this);
			}

			BidirectionalIterator	operator++(int) {
				BidirectionalIterator tmp(*this);
				_ptr++;
				return (tmp);
			}

			bool operator==(const BidirectionalIterator & other) {
				return (_ptr == other._ptr);
			}

			bool operator!=(const BidirectionalIterator & other) {
				return (_ptr != other._ptr);
			}

			protected:
				pointer	_ptr;

		};
	*/

}
#endif

