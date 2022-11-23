/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:46:15 by tnaton            #+#    #+#             */
/*   Updated: 2022/11/23 20:55:43 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
# define RBT_HPP
# include <functional>
# include <limits>
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

			typedef node_base*														node;
			typedef	Key																key_type;
			typedef	T																mapped_type;
			typedef	ft::pair<const Key, T>											value_type;
			typedef	typename Allocator::size_type									size_type;
			typedef	typename Allocator::difference_type								difference_type;
			typedef	Compare															key_compare;
			typedef	Allocator														allocator_type;
			typedef	typename Allocator::reference									reference;
			typedef	typename Allocator::const_reference								const_reference;
			typedef	value_type*														pointer;
			typedef	const value_type*												const_pointer;
			typedef	typename ft::rbtiterator<value_type, key_compare, rbt>			iterator;
			typedef	typename ft::rbtiterator<const value_type, key_compare, rbt>	const_iterator;
			typedef	typename ft::reverse_iterator<iterator>							reverse_iterator;
			typedef	typename ft::reverse_iterator<const_iterator>					const_reverse_iterator;

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
			_size = 0;
		}

		template <class InputIt>
		rbt (InputIt first, InputIt last, const Compare & comp = Compare(), const allocator_type & alloc = allocator_type()) {
			_root = NULL;
			_alloc = alloc;
			_cmp = comp;
			_size = 0;
			insert(first, last);
		}

		rbt (const rbt & other) {
			_root = NULL;
			_alloc = other._alloc;
			_cmp = other._cmp;
			_size = 0;
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
			_size = 0;
			insert(other.begin(), other.end());
			return (*this);
		}

		////////////////////////////////////////
		
		node root(void) const {
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
						_size = 0;
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

	private:
		void rotate(node n, node p) {
			node g = p->parent;
			if (g->l == p) {
				g->l = n;
				p->r = n->l;
				n->l = p;
				if (p->r)
					p->r->parent = p;
			} else {
				g->r = n;
				p->l = n->r;
				n->r = p;
				if (p->l)
					p->l->parent = p;
			}
			n->parent = g;
			p->parent = n;
		}

		void rebalance(node n, node p, node g) {
			if ((g->l == p && p->r == n) || (g->r == p && p->l == n)) {
				rotate(n, p);
				p = n;
			}
			if (g->parent) {
				if (g->parent->l == g)
					g->parent->l = p;
				else
					g->parent->r = p;
			} else {
				_root = p;
			}
			p->parent = g->parent;
			g->parent = p;
			if (g->l == p) {
				g->l = p->r;
				p->r = g;
				if (g->l)
					g->l->parent = g;
			} else {
				g->r = p->l;
				p->l = g;
				if (g->r)
					g->r->parent = g;
			}
			p->color = BLACK;
			g->color = RED;
		}

		void checkInsert(iterator pos) {
			node n = pos.base();
			node p = NULL;

			if (!n->parent) {
				return ;
			}
			do {
				p = n->parent;
				if (p->color == BLACK) {
					return ;
				}
				node g = p->parent;
				if (!g) {
					p->color = BLACK;
					return ;
				}
				node u = (g->l == p ? g->r : g->l);
				if (!u || u->color == BLACK) {
					return rebalance(n, p, g);
				}
				p->color = BLACK;
				u->color = BLACK;
				g->color = RED;
				n = g;
			} while ((p = n->parent) != NULL);
		}

	public:
		iterator insert(iterator pos, const value_type & val) {
			(void)pos;
			ft::pair<iterator, bool> ret = insert(val);
			return (ret.first);
		}

		ft::pair<iterator, bool> insert(const value_type & val) {
			ft::pair<iterator, bool> ret = _insert(val);
			if (ret.second)
				checkInsert(ret.first);
			return (ret);
		}

	private:
		ft::pair<iterator, bool> _insert(const value_type & val) {
			node tmp = _root;

			if (!tmp) {
				tmp = new node_base(val);
				_root = tmp;
				_size++;
				return ft::make_pair(iterator(tmp, this), true);
			}
			while (tmp) {
				if (_cmp(val.first, tmp->val.first)) {
					if (tmp->l) {
						tmp = tmp->l;
					} else {
						tmp->l = new node_base(val);
						tmp->l->parent = tmp;
						_size++;
						return ft::make_pair(iterator(tmp->l, this), true);
					}
				} else if (_cmp(tmp->val.first, val.first)) {
					if (tmp->r) {
						tmp = tmp->r;
					} else {
						tmp->r = new node_base(val);
						tmp->r->parent = tmp;
						_size++;
						return ft::make_pair(iterator(tmp->r, this), true);
					}
				} else {
					return ft::make_pair(iterator(tmp, this), false);
				}
			}
			return ft::make_pair(iterator(tmp, this), true);
		}

	public:
		template< class InputIt >
		void insert(InputIt first, InputIt last) {
			while (first != last) {
				_insert(*first);
				first++;
			}
		}

		void cas6() {
		}
		void cas5() {
		}
		void cas4() {
		}
		void cas3(node p, node s, node c, node d) {
			rotate(s, p);
			(void)c;
			(void)d;
		}

		void _erase(node n) {
			node p = NULL;
			node s = NULL;
			node c = NULL;
			node d = NULL;

			do {
				p = n->parent;
				if (p->l == n) {
					s = p->r;
					c = s->l;
					d = s->r;
				} else {
					s = p->l;
					c = s->r;
					d = s->l;
				}
				if (s->color == RED) {
					return (cas3(p, s, c, d));
				}
				if (d != NULL && d->color == RED) {
					return (cas6());
				}
				if (c != NULL && c->color == RED) {
					return (cas5());
				}
				if (p->color == RED) {
					return (cas4());
				}
				s->color = RED;
				n = p;
			} while ((p = n->parent) != NULL);
		}

		void erase(iterator first, iterator last) {
			Key	val;
			while (first != last) {
				val = first->first;
				first++;
				erase(val);
			}
		}

		size_type erase(const Key & key) {
			std::cout << "n:" << key << std::endl;
			iterator it = find(key);
			if (it == end())
				return (0);
			erase(it);
			return (1);
		}

		void _two_child(node tmp) {
			node	new_root = tmp->r;
			while (new_root->l) {
				new_root = new_root->l;
			}
			ft::swap(tmp, new_root);
		}

		void erase(iterator pos) {
			node tmp = pos.base();

			if (tmp->r && tmp->l) {
				_two_child(tmp);
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
					tmp->r->color = BLACK;
					delete tmp;
				} else {
					if (tmp->parent) {
						if (tmp == tmp->parent->l) {
							tmp->parent->l = tmp->l;
						} else {
							tmp->parent->r = tmp->l;
						}
					}
					tmp->l->parent = tmp->parent;
					if (tmp == _root)
						_root = tmp->l;
					tmp->l->color = BLACK;
					delete tmp;
				}
			} else {
				if (tmp->parent) {
					if (tmp->color == BLACK) {
						_erase(tmp);
					} else {
						if (tmp->parent->l == tmp)
							tmp->parent->l = NULL;
						else
							tmp->parent->r = NULL;
						delete tmp;
					}
				} else {
					delete tmp;
					_root = NULL;
				}
			}
			_size--;
		}

		iterator begin(void) {
			node tmp = _root;
			if (!_root)
				return iterator(_root, this);
			while (tmp->l) {
				tmp = tmp->l;
			}
			return iterator(tmp, this);
		}

		const_iterator begin(void) const {
			node tmp = _root;
			if (!_root)
				return const_iterator(_root, this);
			while (tmp->l) {
				tmp = tmp->l;
			}
			return const_iterator(tmp, this);
		}

		iterator end(void) {
			return iterator(NULL, this);
		}

		const_iterator end(void) const {
			return const_iterator(NULL, this);
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
			return (_size == 0);
		}

		size_type max_size(void) const {
			return std::min(_alloc.max_size(), static_cast<size_type>(std::numeric_limits<difference_type>::max()));
		}

		size_type size(void) const {
			return (_size);
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
					return iterator(tmp, this);
				}
			}
			return iterator(NULL, this);
		}

		const_iterator find(const Key & key) const {
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
					return iterator(tmp, this);
				}
			}
			return iterator(NULL, this);
		}

		T& at(const Key & key) {
			iterator it = find(key);
			if (it == end())
				throw (std::out_of_range("Map out of range"));
			return (it->second);
		}

		const T& at(const Key & key) const {
			const_iterator it = find(key);
			if (it == end())
				throw (std::out_of_range("Map out of range"));
			return (it->second);
		}

		T& operator[](const Key & key) {
			iterator it = find(key);
			if (it == end()) {
				ft::pair<iterator, bool> ret = insert(ft::make_pair<Key, T>(key, T()));
				if (ret.second)
					it = ret.first;
			}
			return (it->second);
		}

		size_type count(const Key & key) const {
			const_iterator it = find(key);
			if (it == end())
				return 0;
			return 1;
		}

		ft::pair<iterator, iterator> equal_range(const Key & key) {
			return (ft::make_pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
		}

		ft::pair<const_iterator, const_iterator> equal_range(const Key & key) const {
			return (ft::make_pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)));
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
						return iterator(tmp, this);
				} else if (_cmp(tmp->val.first, key)) {
					if (tmp->r)
						tmp = tmp->r;
					else
						return iterator(ret, this);
				} else {
					iterator it(tmp, this);
					it++;
					return (it);
				}
			}
			return iterator(NULL, this);
		}

		const_iterator upper_bound(const Key & key) const {
			node tmp = _root;
			node ret = NULL;

			while (tmp) {
				if (_cmp(key, tmp->val.first)) {
					ret = tmp;
					if (tmp->l)
						tmp = tmp->l;
					else
						return const_iterator(tmp, this);
				} else if (_cmp(tmp->val.first, key)) {
					if (tmp->r)
						tmp = tmp->r;
					else
						return const_iterator(ret, this);
				} else {
					const_iterator it(tmp, this);
					it++;
					return (it);
				}
			}
			return const_iterator(NULL, this);
		}

		iterator lower_bound(const Key & key) {
			if (count(key))
				return (find(key));
			else
				return (upper_bound(key));
		}

		const_iterator lower_bound(const Key & key) const {
			if (count(key))
				return (find(key));
			else
				return (upper_bound(key));
		}

		void swap(rbt & other) {
			ft::swap(this->_root, other._root);
			ft::swap(this->_cmp, other._cmp);
			ft::swap(this->_alloc, other._alloc);
			ft::swap(this->_size, other._size);
		}

		key_compare key_comp(void) const {
			return (_cmp);
		}

		private:
			node				_root;
			allocator_type		_alloc;
			key_compare			_cmp;
			size_type			_size;
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
