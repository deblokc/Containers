/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:46:15 by tnaton            #+#    #+#             */
/*   Updated: 2022/12/09 18:36:00 by tnaton           ###   ########.fr       */
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

	template <class Key, class T, class value_type, class Compare, class Allocator = std::allocator<ft::pair<const Key, T> > > class rbt {
		public:

			struct node_base;

			typedef node_base*														node;
			typedef	Key																key_type;
			typedef	T																mapped_type;
			typedef	typename Allocator::size_type									size_type;
			typedef	typename Allocator::difference_type								difference_type;
			typedef	Compare															key_compare;
			typedef	Allocator														allocator_type;
			typedef	typename Allocator::reference									reference;
			typedef	typename Allocator::const_reference								const_reference;
			typedef	value_type*														pointer;
			typedef	const value_type*												const_pointer;
			typedef	typename ft::rbtiterator<value_type, rbt>						iterator;
			typedef	typename ft::rbtiterator<const value_type, rbt>					const_iterator;
			typedef	typename ft::reverse_iterator<iterator>							reverse_iterator;
			typedef	typename ft::reverse_iterator<const_iterator>					const_reverse_iterator;

			struct node_base {
				pointer		val;
				node		parent;
				node		l;
				node		r;
				bool		color;

				~node_base(void) {
					allocator_type	alloc;
					if (val) {
						alloc.destroy(val);
						alloc.deallocate(val, 1);
					}
				}

				node_base(const value_type & value): parent(NULL), l(NULL), r(NULL), color(RED) {
					allocator_type	alloc;
					val = alloc.allocate(1);
					alloc.construct(val, value);
				}

				node_base(node_base const & other): parent(other.parent), l(other.l), r(other.r), color(other.color) {
					allocator_type	alloc;
					val = alloc.allocate(1);
					alloc.construct(val, *other.val);
				}

				node_base & operator=(node_base const & other) {
					if (this == &other)
						return (*this);
					allocator_type	alloc;
					alloc.destroy(val);
					alloc.construct(val, *other.val);
					parent = other.parent;
					l = other.l;
					r = other.r;
					color = other.color;
				}

				void swap(const node & other) {
					if (this->parent == other->parent) {
						ft::swap(this->parent->l, other->parent->r);
					} else {
						if (this->parent && this->parent != other) {
							if (this->parent->l == this) {
								this->parent->l = other;
							} else {
								this->parent->r = other;
							}
						}
						if (other->parent && other->parent != this) {
							if (other->parent->l == other) {
								other->parent->l = this;
							} else {
								other->parent->r = this;
							}
						}
					}
					if (this->l && this->l != other) {
						this->l->parent = other;
					}
					if (this->r && this->r != other) {
						this->r->parent = other;
					}
					if (other->l && other->l != this) {
						other->l->parent = this;
					}
					if (other->r && other->r != this) {
						other->r->parent = this;
					}
					if (this->parent != other && other->parent != this) {
						ft::swap(this->parent, other->parent);
						ft::swap(this->l, other->l);
						ft::swap(this->r, other->r);
					} else if (this->parent == other) {
						this->parent = other->parent;
						other->parent = this;
						if (other->l == this) {
							other->l = this->l;
							this->l = other;
							ft::swap(other->r, this->r);
						} else {
							other->r = this->r;
							this->r = other;
							ft::swap(other->l, this->l);
						}
					} else if (other->parent == this) {
						other->parent = this->parent;
						this->parent = other;
						if (this->l == other) {
							this->l = other->l;
							other->l = this;
							ft::swap(other->r, this->r);
						} else {
							this->r = other->r;
							other->r = this;
							ft::swap(other->l, this->l);
						}
					}
					ft::swap(this->color, other->color);
				}
			};

		explicit rbt(const Compare & comp, const allocator_type & alloc = allocator_type()): _root(NULL), _alloc(alloc), _allocnode(), _cmp(comp), _size(0), _NILL(NULL) {
			_NILL = _allocnode.allocate(1);
			_allocnode.construct(_NILL, value_type());
			_alloc.destroy(_NILL->val);
			_alloc.deallocate(_NILL->val, 1);
			_NILL->val = NULL;
			_NILL->parent = _NILL;
			_root = _NILL;
		}

		template <class InputIt>
		rbt (InputIt first, InputIt last, const Compare & comp, const allocator_type & alloc = allocator_type()): _root(NULL), _alloc(alloc), _allocnode(), _cmp(comp), _size(0), _NILL(NULL) {
			_NILL = _allocnode.allocate(1);
			_allocnode.construct(_NILL, value_type());
			_alloc.destroy(_NILL->val);
			_alloc.deallocate(_NILL->val, 1);
			_NILL->val = NULL;
			_NILL->parent = _NILL;
			_root = _NILL;
			insert(first, last);
		}

		rbt (const rbt & other): _root(NULL), _alloc(other._alloc), _allocnode(), _cmp(other._cmp) {
			_NILL = _allocnode.allocate(1);
			_allocnode.construct(_NILL, value_type());
			_alloc.destroy(_NILL->val);
			_alloc.deallocate(_NILL->val, 1);
			_NILL->val = NULL;
			_NILL->parent = _NILL;
			_root = _NILL;
			_copy(other._root);
			_size = other._size;
		}

		~rbt(void) {
			clear();
			_allocnode.destroy(_NILL);
			_allocnode.deallocate(_NILL, 1);
		}

		rbt & operator=(const rbt & other) {
			if (this == &other)
				return (*this);
			clear();
			_root = _NILL;
			_alloc = other._alloc;
			_cmp = other._cmp;
			_copy(other._root);
			_size = other._size;
			return (*this);
		}

		node root(void) const {
			return _root;
		}

		void clear(void) {
			node tmp = _root;
			node todel = NULL;

			while (_root != _NILL) {
				if (tmp->l) {
					tmp = tmp->l;
				} else if (tmp->r) {
					tmp = tmp->r;
				} else {
					todel = tmp;
					if (!tmp->parent->val) {
						_allocnode.destroy(tmp);
						_allocnode.deallocate(tmp, 1);
						_NILL->parent = _NILL;
						_root = _NILL;
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
					_allocnode.destroy(todel);
					_allocnode.deallocate(todel, 1);
					todel = NULL;
				}
			}
		}

	private:
		void _copy(node root) {
			if (!root->val) {
				_NILL->parent = _NILL;
				_root = _NILL;
				return ;
			}
			node const_tmp = root;
			node tmp = _allocnode.allocate(1);
			_allocnode.construct(tmp, *(const_tmp->val));
			tmp->color = const_tmp->color;
			_root = tmp;
			_NILL->parent = _root;
			_NILL->val = NULL;
			_root->parent = _NILL;
			while (const_tmp->val) {
				if (const_tmp->l && !tmp->l) {
					const_tmp = const_tmp->l;
					tmp->l = _allocnode.allocate(1);
					_allocnode.construct(tmp->l, *(const_tmp->val));
					tmp->l->color = const_tmp->color;
					tmp->l->parent = tmp;
					tmp = tmp->l;
				} else if (const_tmp->r && !tmp->r) {
					const_tmp = const_tmp->r;
					tmp->r = _allocnode.allocate(1);
					_allocnode.construct(tmp->r, *(const_tmp->val));
					tmp->r->color = const_tmp->color;
					tmp->r->parent = tmp;
					tmp = tmp->r;
				} else {
					const_tmp = const_tmp->parent;
					tmp = tmp->parent;
				}
			}
		}

		void rotate(node n, node p) {
			node g = p->parent;

			if (g->val) {
				if (g->l == p) {
					if (p->r == n) {
						g->l = n;
						p->r = n->l;
						n->l = p;
						if (p->r)
							p->r->parent = p;
					} else {
						g->l = n;
						p->l = n->r;
						n->r = p;
						if (p->l)
							p->l->parent = p;
					}
				} else {
					if (p->l == n) {
						g->r = n;
						p->l = n->r;
						n->r = p;
						if (p->l)
							p->l->parent = p;
					} else {
						g->r = n;
						p->r = n->l;
						n->l = p;
						if (p->r)
							p->r->parent = p;
					}
				}
				n->parent = g;
				p->parent = n;
			} else {
				if (p->r == n) {
					p->r = n->l;
					n->l = p;
					if (p->r)
						p->r->parent = p;
				} else {
					p->l = n->r;
					n->r = p;
					if (p->l)
						p->l->parent = p;
				}
				n->parent = NULL;
				p->parent = n;
				_root = n;
				_NILL->parent = _root;
				_root->parent = _NILL;
			}
		}

		void rebalance(node n, node p, node g) {
			if ((g->l == p && p->r == n) || (g->r == p && p->l == n)) {
				rotate(n, p);
				p = n;
			}
			if (g->parent->val) {
				if (g->parent->l == g)
					g->parent->l = p;
				else
					g->parent->r = p;
			} else {
				_root = p;
				_NILL->parent = _root;
				_root->parent = _NILL;
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

		void checkInsert(const_iterator pos) {
			node n = pos.base();
			node p = NULL;

			if (!n->parent->val) {
				return ;
			}
			do {
				p = n->parent;
				if (p->color == BLACK) {
					return ;
				}
				node g = p->parent;
				if (!g->val) {
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
			} while ((p = n->parent) != _NILL);
		}

	public:
		iterator insert(const_iterator pos, const value_type & val) {
			if (pos == begin()) {
				ft::pair<iterator, bool> ret = insert(val);
				return (ret.first);
			}
			const_iterator prepos(pos);
			prepos--;
			if (_cmp(*(prepos.base()->val), val) && (pos == end() || _cmp(val, *(pos.base()->val)))) {
				iterator ret = insert_from_pos(prepos, val);
				checkInsert(ret);
				return (ret);
			}
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
		iterator insert_from_pos(const_iterator pos, const value_type & val) {
			node tmp = pos.base();

			if (tmp == _NILL) {
				tmp = _allocnode.allocate(1);
				_allocnode.construct(tmp, val);
				_root = tmp;
				_NILL->parent = _root;
				_NILL->val = NULL;
				_root->parent = _NILL;
				_size++;
				return iterator(tmp);
			}
			while (tmp->val) {
				if (_cmp(val, *tmp->val)) {
					if (tmp->l) {
						tmp = tmp->l;
					} else {
						tmp->l = _allocnode.allocate(1);
						_allocnode.construct(tmp->l, val);
						tmp->l->parent = tmp;
						_size++;
						return iterator(tmp->l);
					}
				} else if (_cmp(*tmp->val, val)) {
					if (tmp->r) {
						tmp = tmp->r;
					} else {
						tmp->r = _allocnode.allocate(1);
						_allocnode.construct(tmp->r, val);
						tmp->r->parent = tmp;
						_size++;
						return iterator(tmp->r);
					}
				} else {
					return iterator(tmp);
				}
			}
			return iterator(tmp);
		}

		ft::pair<iterator, bool> _insert(const value_type & val) {
			node tmp = _root;

			if (tmp == _NILL) {
				tmp = _allocnode.allocate(1);
				_allocnode.construct(tmp, val);
				_root = tmp;
				_NILL->parent = _root;
				_NILL->val = NULL;
				_root->parent = _NILL;
				_size++;
				return ft::make_pair(iterator(tmp), true);
			}
			while (tmp->val) {
				if (_cmp(val, *tmp->val)) {
					if (tmp->l) {
						tmp = tmp->l;
					} else {
						tmp->l = _allocnode.allocate(1);
						_allocnode.construct(tmp->l, val);
						tmp->l->parent = tmp;
						_size++;
						return ft::make_pair(iterator(tmp->l), true);
					}
				} else if (_cmp(*tmp->val, val)) {
					if (tmp->r) {
						tmp = tmp->r;
					} else {
						tmp->r = _allocnode.allocate(1);
						_allocnode.construct(tmp->r, val);
						tmp->r->parent = tmp;
						_size++;
						return ft::make_pair(iterator(tmp->r), true);
					}
				} else {
					return ft::make_pair(iterator(tmp), false);
				}
			}
			return ft::make_pair(iterator(tmp), true);
		}

	public:
		template< class InputIt >
		void insert(InputIt first, InputIt last) {
			while (first != last) {
				insert(*first);
				first++;
			}
		}

		void cas6(node p, node s, node d) {
			rotate(s, p);
			s->color = p->color;
			p->color = BLACK;
			d->color = BLACK;
			return ;
		}

		void cas5(node p, node s, node c, node d) {
			rotate(c, s);
			s->color = RED;
			c->color = BLACK;
			d = s;
			s = c;
			return cas6(p, s, d);
		}

		void cas4(node s, node p) {
			s->color = RED;
			p->color = BLACK;
			return ;
		}

		void cas3(bool isleft, node p, node s, node c, node d) {
			rotate(s, p);
			p->color = RED;
			s->color = BLACK;
			s = c;
			d = (isleft ? s->r : s->l);
			if (d != NULL && d->color == RED) {
				return cas6(p, s, d);
			}
			c = (isleft ? s->l : s->r);
			if (c != NULL && c->color == RED) {
				return cas5(p, s, c, d);
			}
			return (cas4(s, p));
		}

		void _erase(node n) {
			node p = NULL;
			node s = NULL;
			node c = NULL;
			node d = NULL;
			bool	isleft;

			p = n->parent;
			isleft = p->l == n;
			if (isleft)
				p->l = NULL;
			else
				p->r = NULL;
			_allocnode.destroy(n);
			_allocnode.deallocate(n, 1);
			n = NULL;
			do {
				if (n)
					isleft = p->l == n;
				s = (isleft ? p->r : p->l);
				c = (isleft ? s->l : s->r);
				d = (isleft ? s->r : s->l);
				if (s->color == RED) {
					return (cas3(isleft, p, s, c, d));
				}
				if (d != NULL && d->color == RED) {
					return (cas6(p, s, d));
				}
				if (c != NULL && c->color == RED) {
					return (cas5(p, s, c, d));
				}
				if (p->color == RED) {
					return (cas4(s, p));
				}
				s->color = RED;
				n = p;
			} while ((p = n->parent) != _NILL);
		}

		void erase(const_iterator first, const_iterator last) {
			const_iterator	val;
			while (first != last) {
				val = first;
				first++;
				erase(val);
			}
		}

		size_type erase(const Key & key) {
			const_iterator it = find(key);
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
			if (tmp == _root) {
				_root = new_root;
				tmp->swap(new_root);
				_NILL->parent = _root;
				_root->parent = _NILL;
			} else {
				tmp->swap(new_root);
			}
		}

		void erase(const_iterator pos) {
			node tmp = pos.base();

			if (tmp->r && tmp->l) {
				_two_child(tmp);
			}
			if (tmp->r || tmp->l) {
				if (tmp->r) {
					if (tmp->parent->val) {
						if (tmp == tmp->parent->l) {
							tmp->parent->l = tmp->r;
						} else {
							tmp->parent->r = tmp->r;
						}
					}
					tmp->r->parent = tmp->parent;
					if (tmp == _root) {
						_root = tmp->r;
						_NILL->parent = _root;
						_root->parent = _NILL;
					}
					tmp->r->color = BLACK;
					_allocnode.destroy(tmp);
					_allocnode.deallocate(tmp, 1);
				} else {
					if (tmp->parent->val) {
						if (tmp == tmp->parent->l) {
							tmp->parent->l = tmp->l;
						} else {
							tmp->parent->r = tmp->l;
						}
					}
					tmp->l->parent = tmp->parent;
					if (tmp == _root) {
						_root = tmp->l;
						_NILL->parent = _root;
						_root->parent = _NILL;
					}
					tmp->l->color = BLACK;
					_allocnode.destroy(tmp);
					_allocnode.deallocate(tmp, 1);
				}
			} else {
				if (tmp->parent->val) {
					if (tmp->color == BLACK) {
						_erase(tmp);
					} else {
						if (tmp->parent->l == tmp)
							tmp->parent->l = NULL;
						else
							tmp->parent->r = NULL;
						_allocnode.destroy(tmp);
						_allocnode.deallocate(tmp, 1);
					}
				} else {
					_allocnode.destroy(tmp);
					_allocnode.deallocate(tmp, 1);
					_NILL->parent = _NILL;
					_root = _NILL;
				}
			}
			_size--;
		}

		iterator begin(void) {
			node tmp = _root;
			if (!_root->val)
				return iterator(_root);
			while (tmp->l) {
				tmp = tmp->l;
			}
			return iterator(tmp);
		}

		const_iterator begin(void) const {
			node tmp = _root;
			if (!_root->val)
				return const_iterator(_root);
			while (tmp->l) {
				tmp = tmp->l;
			}
			return const_iterator(tmp);
		}

		iterator end(void) {
			return iterator(_NILL);
		}

		const_iterator end(void) const {
			return const_iterator(_NILL);
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
			return const_reverse_iterator(begin());
		}

		bool empty(void) const {
			return (_size == 0);
		}

		size_type max_size(void) const {
			return (_allocnode.max_size());
		}

		size_type size(void) const {
			return (_size);
		}

		iterator find(const Key & key) {
			node tmp = _root;

			while (tmp->val) {
				if (_cmp(key, *tmp->val)) {
					if (tmp->l) {
						tmp = tmp->l;
					} else {
						break ;
					}
				} else if (_cmp(*tmp->val, key)) {
					if (tmp->r) {
						tmp = tmp->r;
					} else {
						break ;
					}
				} else {
					return iterator(tmp);
				}
			}
			return iterator(_NILL);
		}

		const_iterator find(const Key & key) const {
			node tmp = _root;

			while (tmp->val) {
				if (_cmp(key, *tmp->val)) {
					if (tmp->l) {
						tmp = tmp->l;
					} else {
						break ;
					}
				} else if (_cmp(*tmp->val, key)) {
					if (tmp->r) {
						tmp = tmp->r;
					} else {
						break ;
					}
				} else {
					return iterator(tmp);
				}
			}
			return iterator(_NILL);
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
			node ret = _NILL;

			while (tmp->val) {
				if (_cmp(key, *tmp->val)) {
					ret = tmp;
					if (tmp->l)
						tmp = tmp->l;
					else
						return iterator(tmp);
				} else if (_cmp(*tmp->val, key)) {
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
			return iterator(_NILL);
		}

		const_iterator upper_bound(const Key & key) const {
			node tmp = _root;
			node ret = _NILL;

			while (tmp->val) {
				if (_cmp(key, *tmp->val)) {
					ret = tmp;
					if (tmp->l)
						tmp = tmp->l;
					else
						return const_iterator(tmp);
				} else if (_cmp(*tmp->val, key)) {
					if (tmp->r)
						tmp = tmp->r;
					else
						return const_iterator(ret);
				} else {
					const_iterator it(tmp);
					it++;
					return (it);
				}
			}
			return const_iterator(_NILL);
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
			ft::swap(this->_NILL, other._NILL);
			key_compare test = _cmp;
			this->_cmp = other._cmp;
			other._cmp = test;
			ft::swap(this->_alloc, other._alloc);
			ft::swap(this->_size, other._size);
		}

		key_compare key_comp(void) const {
			return (_cmp);
		}

		private:
			node						_root;
			allocator_type				_alloc;
			std::allocator<node_base>	_allocnode;
			key_compare					_cmp;
			size_type					_size;
			node						_NILL;
	};

	template<class Key, class T, class value_type, class Compare, class Alloc>
	void swap(ft::rbt<Key, T, value_type, Compare, Alloc> & lhs, ft::rbt<Key, T, value_type, Compare, Alloc> & rhs) {
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
