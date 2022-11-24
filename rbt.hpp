/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:46:15 by tnaton            #+#    #+#             */
/*   Updated: 2022/11/24 18:37:36 by tnaton           ###   ########.fr       */
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

		struct Trunk
		{
			Trunk *prev;
			std::string str;
		 
			Trunk(Trunk *prev, std::string str)
			{
				this->prev = prev;
				this->str = str;
			}
		};

		void showTrunks(Trunk *p)
		{
			if (p == NULL) {
				return;
			}

			showTrunks(p->prev);
			std::cout << p->str;
		}

		void printTree(node root, Trunk *prev, bool isLeft) {
			if (root == NULL)
				return ;
		//	std::cout << "root : " << root->val.first << std::endl;
			std::string prev_str = "         ";
			Trunk *trunk = new Trunk(prev, prev_str);

			printTree(root->r, trunk, true);

			if (!prev) {
				trunk->str = "—————————";
			}
			else if (isLeft)
			{
				trunk->str = ".—————————";
				prev_str = "         |";
			}
			else {
				trunk->str = "`—————————";
				prev->str = prev_str;
			}

			showTrunks(trunk);
			if (root->color)
				std::cout << "\033[0;90m"; 
			else
				std::cout << "\033[0;91m";
			std::cout << " " << root->val.first << "\033[0m" << std::endl;

			if (prev) {
				prev->str = prev_str;
			}
			trunk->str = "         |";

			printTree(root->l, trunk, false);
			delete trunk;
		}

		void debug(void) {
			printTree(_root, NULL, false);
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

			if (g) {
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
			}
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
			delete n;
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
			} while ((p = n->parent) != NULL);
		}

		void erase(iterator first, iterator last) {
			iterator	val;
			while (first != last) {
				val = first;
				first++;
				erase(val);
			}
		}

		size_type erase(const Key & key) {
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
			if (tmp == _root) {
				_root = new_root;
			}
			tmp->swap(new_root);
		}

		void erase(iterator pos) {
			node tmp = pos.base();

			if (tmp->r && tmp->l) {
				_two_child(tmp);
			}
			if (tmp->r || tmp->l) {
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
