/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:11:34 by tnaton            #+#    #+#             */
/*   Updated: 2022/11/30 15:27:53 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP
# include <iterator>

namespace ft {

	template <typename T>
	struct remove_const {
		typedef T type;
	};

	template <typename T>
	struct remove_const<const T> {
		typedef T type;
	};

	template <typename T>
	struct remove_volatile {
		typedef T type;
	};

	template <typename T>
	struct remove_volatile<volatile T> {
		typedef T type;
	};

	template <typename T>
	struct remove_volatile_const {
		typedef typename remove_volatile<typename remove_const<T>::type>::type type;
	};

	template<class Iter>
	struct iterator_traits {
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template<class T>
	struct iterator_traits<T*> {
		typedef std::ptrdiff_t								difference_type;
		typedef typename remove_volatile_const<T>::type		value_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef typename std::random_access_iterator_tag	iterator_category;
	};
}

#endif
