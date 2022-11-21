/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:46:15 by tnaton            #+#    #+#             */
/*   Updated: 2022/11/21 21:19:33 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
# define RBT_HPP
# include <functional>
# include "utils.hpp"
# include "reverse_iterator.hpp"
# include "rbtiterator.hpp"
# ifndef BLACK
# define BLACK 1
# endif
# ifndef RED
# define RED 0
# endif

namespace ft {

	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > > class rbt {
		public:

			struct node_base;

			typedef node_base*													node;
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
			typedef	const value_type*											const_pointer;
			typedef	typename ft::rbtiterator<pointer, key_compare, rbt>			iterator;
			typedef	typename ft::rbtiterator<const_pointer, key_compare, rbt>	const_iterator;
			typedef	typename ft::reverse_iterator<iterator>						reverse_iterator;
			typedef	typename ft::reverse_iterator<const_iterator>				const_reverse_iterator;

			struct node_base {
				value_type	val;
				node		parent;
				node		l;
				node		r;
				bool		color;
				bool		end;

				node_base(const value_type & val = value_type()): val(val), parent(NULL), l(NULL), r(NULL), color(RED), end(false) {}
				node_base(node_base const & other): val(other.val), parent(other.parent), l(other.l), r(other.r), color(other.color), end(other.end) {}

			};

		explicit rbt(const Compare & comp = Compare(), const allocator_type & alloc = allocator_type()) {
			_root = NULL;
			_alloc = alloc;
			_cmp = comp;
		}

		template <class InputIt>
		rbt (InputIt first, InputIt last, const Compare & comp = Compare(), const allocator_type & alloc = allocator_type()) {
			_root = NULL;
			_alloc = alloc;
			_cmp = comp;
			insert(first, last);
		}

		rbt (const rbt & other) {
			_root = NULL;
			_alloc = other._alloc;
			_cmp = other._cmp;
			insert(other.begin(), other.end());
		}

		~rbt(void) {
			clear();
		}

		rbt & operator=(const rbt & other) {
			if (this == &other)
				return (*this);
			clear();
			_root = NULL;
			_alloc = other._alloc;
			_cmp = other._cmp;
			insert(other.begin(), other.end());
			return (*this);
		}

		////////////////////////////////////////
		
		node root(void) {
			return (_root);
		}
		
		////////////////////////////////////////

		void clear(void) {
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
					if (tmp->l) {
					}
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

		ft::pair<iterator, bool> insert(const value_type & val) {
			node tmp = _root;

			if (!tmp) {
				_root = new node_base(val);
				tmp = _root;
			}
			while (tmp) {
				if (_cmp(val.first, tmp->val.first)) {
					if (tmp->l) {
						tmp = tmp->l;
					} else {
						tmp->l = new node_base(val);
						tmp->l->parent = tmp;
						return ft::make_pair(iterator(tmp->l), true);
					}
				} else if (_cmp(tmp->val.first, val.first)) {
					if (tmp->r) {
						tmp = tmp->r;
					} else {
						tmp->r = new node_base(val);
						tmp->r->parent = tmp;
						return ft::make_pair(iterator(tmp->r), true);
					}
				} else {
					return ft::make_pair(iterator(tmp), false);
				}
			}
			return ft::make_pair(iterator(tmp), true);
		}

		template< class InputIt >
		void insert(InputIt first, InputIt last) {
			while (first != last) {
				insert(*first);
				first++;
			}
		}

		size_type erase(const Key & key) {
			iterator it = find(key);
			if (it == end())
				return (0);
			erase(it);
			return (1);
		}

		void erase(iterator pos) {
			node tmp = pos.base();

			if (tmp->r && tmp->l) {
				node	new_root = tmp->r;
				while (new_root->l) {
					new_root = new_root->l;
				}
				if (tmp->l)
					tmp->l->parent = new_root;
				if (tmp->r)
					tmp->r->parent = new_root;
				if (new_root->r) {
					new_root->r->parent = new_root->parent;
					new_root->parent->l = new_root->r;
				} else {
					new_root->parent->l = NULL;
				}
				if (tmp->parent) {
					if (tmp == tmp->parent->l) {
						tmp->parent->l = new_root;
					} else {
						tmp->parent->r = new_root;
					}
				}
				new_root->parent = tmp->parent;
				new_root->l = tmp->l;
				new_root->r = tmp->r;
				if (tmp == _root)
					_root = new_root;
				delete tmp;
			} else if (tmp->r || tmp->l) {
				if (tmp->r) {
					if (tmp->parent) {
						if (tmp == tmp->parent->l) {
							tmp->parent->l = tmp->r;
						} else {
							tmp->parent->r = tmp->r;
						}
					}
					tmp->r->parent = tmp->parent;
					if (tmp == _root)
						_root = tmp->r;
					delete tmp;
				} else {
					if (tmp->parent) {
						if (tmp == tmp->parent->l) {
							tmp->parent->l = tmp->l;
						} else {
							tmp->parent->r = tmp->l;
						}
					}
					tmp->r->parent = tmp->parent;
					if (tmp == _root)
						_root = tmp->r;
					delete tmp;
				}
			} else {
				if (tmp->parent) {
					if (tmp == tmp->parent->l)
						tmp->parent->l = NULL;
					else
						tmp->parent->r = NULL;
				} else {
					_root = NULL;
				}
				delete tmp;
			}
		}

		iterator begin(void) {
			node tmp = _root;
			if (!_root)
				return iterator(_root);
			while (tmp->l) {
				tmp = tmp->l;
			}
			return iterator(tmp);
		}

		const_iterator begin(void) const {
			node tmp = _root;
			if (!_root)
				return const_iterator(_root);
			while (tmp->l) {
				tmp = tmp->l;
			}
			return const_iterator(tmp);
		}

		iterator end(void) {
			return iterator(NULL);
		}

		const_iterator end(void) const {
			return const_iterator(NULL);
		}

		reverse_iterator rbegin(void) {
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin(void) const {
			return const_reverse_iterator(end());
		}

		reverse_iterator rend(void) {
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend(void) const {
			return const_reverse_iterator(end());
		}

		bool empty(void) const {
			return (begin() == end());
		}

		size_type max_size(void) const {
			return (_alloc.max_size());
		}

		size_type size(void) const {
			size_type i = 0;
			for (iterator it = iterator(_root); it != end(); it++) {
				i++;
			}
			return (i);
		}

		iterator find(const Key & key) {
			node tmp = _root;

			while (tmp) {
				if (_cmp(key, tmp->val.first)) {
					if (tmp->l) {
						tmp = tmp->l;
					} else {
						break ;
					}
				} else if (_cmp(tmp->val.first, key)) {
					if (tmp->r) {
						tmp = tmp->r;
					} else {
						break ;
					}
				} else {
					return iterator(tmp);
				}
			}
			return iterator(NULL);
		}

		T& at(const Key & key) {
			iterator it = find(key);
			if (it == end())
				throw (std::out_of_range("Map out of range"));
			return (it->second);
		}

		T& operator[](const Key & key) {
			iterator it = find(key);
			if (it == end()) {
				it = insert(ft::make_pair<Key, T>(key, T()));
			}
			return (it->second);
		}

		size_type count(const Key & key) const {
			iterator it = find(key);
			if (it == end())
				return 0;
			return 1;
		}

		ft::pair<iterator, iterator> equal_range(const Key & key) {
			return (ft::make_pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
		}

		iterator upper_bound(const Key & key) {
			node tmp = _root;
			node ret = NULL;

			while (tmp) {
				if (_cmp(key, tmp->val.first)) {
					ret = tmp;
					if (tmp->l)
						tmp = tmp->l;
					else
						return iterator(tmp);
				} else if (_cmp(tmp->val.first, key)) {
					if (tmp->r)
						tmp = tmp->r;
					else
						return iterator(ret);
				} else {
					iterator it(tmp);
					it++;
					return (it);
				}
			}
			return iterator(NULL);
		}

		iterator lower_bound(const Key & key) {
			node tmp = _root;
			node ret = NULL;

			while (tmp) {
				if (_cmp(key, tmp->val.first)) {
					if (tmp->l)
						tmp = tmp->l;
					else
						return iterator(ret);
				} else if (_cmp(tmp->val.first, key)) {
					ret = tmp;
					if (tmp->r)
						tmp = tmp->r;
					else
						return iterator(tmp);
				} else {
					return iterator(tmp);
				}
			}
			return iterator(NULL);
		}

		void swap(rbt & other) {
			ft::swap(this->_root, other._root);
			ft::swap(this->_cmp, other._cmp);
		}

		private:
			node				_root;
			allocator_type		_alloc;
			key_compare			_cmp;
	};

	template<class Key, class T, class Compare, class Alloc>
	void swap(ft::rbt<Key, T, Compare, Alloc> & lhs, ft::rbt<Key, T, Compare, Alloc> & rhs) {
		lhs.swap(rhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::rbt<Key, T, Compare, Alloc> & lhs, const ft::rbt<Key, T, Compare, Alloc> & rhs) {
		return ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(const ft::rbt<Key, T, Compare, Alloc> & lhs, const ft::rbt<Key, T, Compare, Alloc> & rhs) {
		return !(lhs == rhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<(const ft::rbt<Key, T, Compare, Alloc> & lhs, const ft::rbt<Key, T, Compare, Alloc> & rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=(const ft::rbt<Key, T, Compare, Alloc> & lhs, const ft::rbt<Key, T, Compare, Alloc> & rhs) {
		return !(lhs < rhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>(const ft::rbt<Key, T, Compare, Alloc> & lhs, const ft::rbt<Key, T, Compare, Alloc> & rhs) {
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=(const ft::rbt<Key, T, Compare, Alloc> & lhs, const ft::rbt<Key, T, Compare, Alloc> & rhs) {
		return !(lhs > rhs);
	}
}

#endif
