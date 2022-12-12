/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:49:48 by tnaton            #+#    #+#             */
/*   Updated: 2022/12/12 18:13:32 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP
# include "inc/rbt.hpp"
namespace ft {

	template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
	class set {
		public:

			typedef	Key																	key_type;
			typedef	Key																	value_type;
			typedef	typename Allocator::size_type										size_type;
			typedef	typename Allocator::difference_type									difference_type;
			typedef	Compare																key_compare;
			typedef	Compare																value_compare;
			typedef	Allocator															allocator_type;
			typedef	typename Allocator::reference										reference;
			typedef	typename Allocator::const_reference									const_reference;
			typedef	value_type*															pointer;
			typedef	typename Allocator::const_pointer									const_pointer;
		private:
			typedef	typename ft::rbt<Key, Key, value_type, value_compare, Allocator>	rbt;
		public:
			typedef	typename ft::rbtiterator<const value_type, rbt>						iterator;
			typedef	typename ft::rbtiterator<const value_type, rbt>						const_iterator;
			typedef	typename ft::reverse_iterator<iterator>								reverse_iterator;
			typedef	typename ft::reverse_iterator<const_iterator>						const_reverse_iterator;

			explicit set(const Compare & comp = Compare(), const allocator_type & alloc = allocator_type()): _tree(comp, alloc) {
			}

			template <class InputIt>
			set (InputIt first, InputIt last, const Compare & comp = Compare(), const allocator_type & alloc = allocator_type()): _tree(first, last, comp, alloc) {
			}

			set (const set & other): _tree(other._tree) {
			}

			~set(void) {
			}

			set &operator=(const set & other) {
				if (this == &other)
					return (*this);
				_tree = other._tree;
				return (*this);
			}

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

			iterator insert(iterator pos, const value_type & val) {
				return (_tree.insert(pos, val));
			}

			void erase(iterator first, iterator last) {
				_tree.erase(first, last);
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

			const_iterator find(const Key & key) const {
				return (_tree.find(key));
			}

			size_type count(const Key & key) const {
				return (_tree.count(key));
			}

			ft::pair<iterator, iterator> equal_range(const Key & key) {
				return (_tree.equal_range(key));
			}

			ft::pair<const_iterator, const_iterator> equal_range(const Key & key) const {
				return (_tree.equal_range(key));
			}

			iterator upper_bound(const Key & key) {
				return (_tree.upper_bound(key));
			}

			const_iterator upper_bound(const Key & key) const {
				return (_tree.upper_bound(key));
			}

			iterator lower_bound(const Key & key) {
				return (_tree.lower_bound(key));
			}

			const_iterator lower_bound(const Key & key) const {
				return (_tree.lower_bound(key));
			}

			allocator_type get_allocator(void) const {
				return (allocator_type());
			}

			void swap(set & other) {
				ft::swap(_tree, other._tree);
			}

			key_compare key_comp(void) const {
				return (_tree.key_comp());
			}

			value_compare	value_comp(void) const {
				return (key_comp());
			}

		private:
			rbt	_tree;
	};

	template<class Key, class Compare, class Alloc>
	void swap(ft::set<Key, Compare, Alloc> & lhs, ft::set<Key, Compare, Alloc> & rhs) {
		lhs.swap(rhs);
	}

	template<class Key, class Compare, class Alloc>
	bool operator==(const ft::set<Key, Compare, Alloc> & lhs, const ft::set<Key, Compare, Alloc> & rhs) {
		return ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template<class Key, class Compare, class Alloc>
	bool operator!=(const ft::set<Key, Compare, Alloc> & lhs, const ft::set<Key, Compare, Alloc> & rhs) {
		return !(lhs == rhs);
	}

	template<class Key, class Compare, class Alloc>
	bool operator<(const ft::set<Key, Compare, Alloc> & lhs, const ft::set<Key, Compare, Alloc> & rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class Key, class Compare, class Alloc>
	bool operator>=(const ft::set<Key, Compare, Alloc> & lhs, const ft::set<Key, Compare, Alloc> & rhs) {
		return !(lhs < rhs);
	}

	template<class Key, class Compare, class Alloc>
	bool operator>(const ft::set<Key, Compare, Alloc> & lhs, const ft::set<Key, Compare, Alloc> & rhs) {
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template<class Key, class Compare, class Alloc>
	bool operator<=(const ft::set<Key, Compare, Alloc> & lhs, const ft::set<Key, Compare, Alloc> & rhs) {
		return !(lhs > rhs);
	}

}

#endif
