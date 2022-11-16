/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:46:15 by tnaton            #+#    #+#             */
/*   Updated: 2022/11/16 20:03:31 by tnaton           ###   ########.fr       */
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

	template <class T, class Allocator = std::allocator<T> > struct node {
		public:
			node(void): _value(), _parent(NULL), _lchild(NULL), _rchild(NULL), color(BLACK) {}
			node(const T & value, node *parent): _value(value), _parent(parent), _lchild(NULL), _rchild(NULL), color(!parent.color) {}

			void addlchild(T value) {
				_lchild = node(value, this);
			}

			void addrchild(T value) {
				_rchild = node(value, this);
			}

			bool getColor(void) const {
				return color;
			}

			T	getVal(void) const {
				return _value;
			}

		private:
			T		_value;
			node<T>	*_parent;
			node<T>	*_lchild;
			node<T>	*_rchild;
			bool	color;
	};

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

		explicit rbt(const allocator_type & alloc = allocator_type()) {
			_root = NULL;
			_alloc = alloc();
		}

		std::pair<pointer, bool> insert(const value_type &value) {
			node<value_type>	ptr;

			while (ptr) {
				if (ptr.getVal() == value)
					return (ptr);
				ptr = ((ptr.getVal() < value) ? ptr._lchild : ptr._rchild);
			}
			if (ptr.parent.getVal() < value) {
				ptr.parent.addlchild(value);
			} else {
				ptr.parent.addrchild(value);
			}
			return (ptr);
		}

		private:
			node<value_type>	_root;
			allocator_type		_alloc;
	};
}

#endif
