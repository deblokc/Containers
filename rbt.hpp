/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:46:15 by tnaton            #+#    #+#             */
/*   Updated: 2022/11/19 16:31:53 by tnaton           ###   ########.fr       */
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
#include <iostream>

namespace ft {

	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > > class rbt {
		public:
			typedef	Key										key_type;
			typedef	T										mapped_type;
			typedef	ft::pair<Key, T>					value_type;
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

				node_base(const value_type & val = value_type()): val(val), parent(NULL), l(NULL), r(NULL), color(RED) {}
				node_base(node_base const & other): val(other.val), parent(other.parent), l(other.l), r(other.r), color(other.color) {
				std::cout << "lecaca" << std::endl;
				}
			};

		explicit rbt(const allocator_type & alloc = allocator_type()) {
			_root = NULL;
			_alloc = alloc;
		}

		~rbt(void) {
			node tmp = _root;
			node todel = NULL;

			while (_root) {
				if (tmp->l) {
					tmp = tmp->l;
				} else if (tmp->r) {
					tmp = tmp->r;
				} else {
					todel = tmp;
					if (!tmp->parent) {
						delete tmp;
						_root = NULL;
						return ;
					}
					tmp = tmp->parent;
					if (tmp->l && todel == tmp->l)
						tmp->l = NULL;
					else
						tmp->r = NULL;
				}
				if (todel) {
					delete todel;
					todel = NULL;
				}
			}
		}

		node insert(const value_type & val) {
			node tmp = _root;

			if (!tmp) {
				_root = new node_base(val);
				tmp = _root;
			}
			while (tmp) {
				if (val.first < tmp->val.first) {
					if (tmp->l) {
						tmp = tmp->l;
					} else {
						tmp->l = new node_base(val);
						tmp->l->parent = tmp;
						return (tmp->l);
					}
				} else if (val.first > tmp->val.first) {
					if (tmp->r) {
						tmp = tmp->r;
					} else {
						tmp->r = new node_base(val);
						tmp->r->parent = tmp;
						return (tmp->r);
					}
				} else {
					return (tmp);
				}
			}
			return (tmp);
		}

		private:
			node				_root;
			allocator_type		_alloc;
	};
}

#endif
