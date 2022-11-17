/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:46:15 by tnaton            #+#    #+#             */
/*   Updated: 2022/11/17 20:03:56 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
# define RBT_HPP
# include <functional>
# include "utils.hpp"
# ifndef BLACK
# define BLACK 1
# endif
# ifndef RED
# define RED 0
# endif

namespace ft {

	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > > class rbt {
		public:
			typedef	Key										key_type;
			typedef	T										mapped_type;
			typedef	ft::pair<const Key, T>					value_type;
			typedef	typename Allocator::size_type			size_type;
			typedef	typename Allocator::difference_type		difference_type;
			typedef	Compare									key_compare;
			typedef	Allocator								allocator_type;
			typedef	typename Allocator::reference			reference;
			typedef	typename Allocator::const_reference		const_reference;
			typedef	typename Allocator::pointer				pointer;
			typedef	typename Allocator::const_pointer		const_pointer;

			struct node_base;
			typedef node_base*								node;

			struct node_base {
				value_type	val;
				node		parent;
				node		l;
				node		r;
				bool		color;

				node_base(const_reference val = value_type()): val(val), parent(NULL), l(NULL), r(NULL), color(BLACK) {}
				node_base(node_base const & other): val(other.val), parent(other.parent), l(other.l), r(other.r), color(other.color) {}
			};

		explicit rbt(const allocator_type & alloc = allocator_type()) {
			_root = NULL;
			_alloc = alloc;
		}

		private:
			node				_root;
			allocator_type		_alloc;
	};
}

#endif
