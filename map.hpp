/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:49:48 by tnaton            #+#    #+#             */
/*   Updated: 2022/11/21 21:14:21 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
# include "rbt.hpp"

namespace ft {

	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map {
		public:

			typedef	typename ft::rbt<Key, T, Compare, Allocator>				rbt;
			typedef	Key															key_type;
			typedef	T															mapped_type;
			typedef	ft::pair<const Key, T>										value_type;
			typedef	typename Allocator::size_type								size_type;
			typedef	typename Allocator::difference_type							difference_type;
			typedef	Compare														key_compare;
			typedef	Allocator													allocator_type;
			typedef	typename Allocator::reference								reference;
			typedef	typename Allocator::const_reference							const_reference;
			typedef	value_type*													pointer;
			typedef	typename Allocator::const_pointer							const_pointer;
			typedef	typename ft::rbtiterator<pointer, key_compare, rbt>			iterator;
			typedef	typename ft::rbtiterator<const_pointer, key_compare, rbt>	const_iterator;
			typedef	typename ft::reverse_iterator<iterator>						reverse_iterator;
			typedef	typename ft::reverse_iterator<const_iterator>				const_reverse_iterator;

			explicit map(const Compare & comp = Compare(), const allocator_type & alloc = allocator_type()): _tree(comp, alloc) {
			}

			template <class InputIt>
			map (InputIt first, InputIt last, const Compare & comp = Compare(), const allocator_type & alloc = allocator_type()): _tree(first, last, comp, alloc) {
			}

			map (const map & other): _tree(other._tree) {
			}

			~map(void) {
			}

			map &operator=(const map & other) {
				if (this == &other)
					return (*this);
				_tree = other._tree;
				return (*this);
			}

			////////////////////////////////////
			
			typename rbt::node root(void) {
				return _tree.root();
			}

			////////////////////////////////////

			void clear(void) {
				_tree.clear();
			}

			ft::pair<iterator, bool> insert(const value_type & val) {
				return (_tree.insert(val));
			}

			template <class InputIt>
			void insert(InputIt first, InputIt last) {
				_tree.insert(first, last);
			}

			void erase(iterator pos) {
				_tree.erase(pos);
			}

			size_type erase(const Key & key) {
				return (_tree.erase(key));
			}

			iterator begin(void) {
				return (_tree.begin());
			}

			const_iterator begin(void) const {
				return (_tree.begin());
			}

			iterator end(void) {
				return (_tree.end());
			}

			const_iterator end(void) const {
				return (_tree.end());
			}

			reverse_iterator rend(void) {
				return (_tree.rend());
			}

			const_reverse_iterator rend(void) const {
				return (_tree.rend());
			}

			reverse_iterator rbegin(void) {
				return (_tree.rbegin());
			}

			const_reverse_iterator rbegin(void) const {
				return (_tree.rbegin());
			}

			bool empty(void) const {
				return (_tree.empty());
			}

			size_type max_size(void) const {
				return (_tree.max_size());
			}

			size_type size(void) const {
				return (_tree.size());
			}

			iterator find(const Key & key) {
				return (_tree.find(key));
			}

			T& at(const Key & key) {
				return (_tree.at(key));
			}

			T& operator[](const Key & key) {
				return (_tree[key]);
			}

			size_type count(const Key & key) const {
				return (_tree.count(key));
			}

			ft::pair<iterator, iterator> equal_range(const Key & key) {
				return (_tree.equal_range(key));
			}

			iterator upper_bound(const Key & key) {
				return (_tree.upper_bound(key));
			}

			iterator lower_bound(const Key & key) {
				return (_tree.lower_bound(key));
			}

			void swap(map & other) {
				ft::swap(_tree, other._tree);
			}

		private:
			rbt	_tree;
	};

	template<class Key, class T, class Compare, class Alloc>
	void swap(ft::map<Key, T, Compare, Alloc> & lhs, ft::map<Key, T, Compare, Alloc> & rhs) {
		lhs.swap(rhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs) {
		return (lhs._tree == rhs._tree);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs) {
		return (lhs._tree != rhs._tree);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs) {
		return (lhs._tree < rhs._tree);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs) {
		return (lhs._tree >= rhs._tree);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs) {
		return (lhs._tree > rhs._tree);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs) {
		return (lhs._tree <= rhs._tree);
	}
}

#endif
