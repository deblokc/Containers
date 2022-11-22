/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtiterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:07:10 by tnaton            #+#    #+#             */
/*   Updated: 2022/11/20 19:45:43 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iterator_traits.hpp"
#include "utils.hpp"
#include <iostream>

namespace ft {

	template <typename T, typename cmp, typename ctnr>
	class rbtiterator {
		public:
			typedef T													iterator_type;
			typedef std::bidirectional_iterator_tag						iterator_category;
			typedef T													value_type;
			typedef typename ctnr::difference_type						difference_type;
			typedef T &													reference;
			typedef T *													pointer;
			typedef typename ctnr::node									node;
			typedef typename ctnr::node_base							node_base;

			rbtiterator(void): _ptr() {}
			explicit rbtiterator(const node & other_ptr, const ctnr * tree): _ptr(other_ptr), _tree(tree) {}

			template <typename Ptr>
			rbtiterator(const rbtiterator<Ptr, cmp, typename enable_if<is_same<Ptr, typename ctnr::pointer>::val, ctnr>::type> & other) : _ptr(other.base()), _tree(other._tree) {}

			~rbtiterator() {
			}

			rbtiterator & operator=(const rbtiterator & other) {
				if (this == &other)
					return (*this);
				this->_ptr = other._ptr;
				this->_tree = other._tree;
				return (*this);
			}

			const node base(void) const {return _ptr;}
			reference operator*(void) const {return (_ptr->val);}
			pointer operator->(void) {return &(_ptr->val);}
			pointer operator->(void) const {return &(_ptr->val);}

			rbtiterator & operator++(void) {
				if (_ptr->r) {
					_ptr = _ptr->r;
					while (_ptr->l) {
						_ptr = _ptr->l;
					}
					return (*this);
				} else {
					value_type tmp = _ptr->val;
					while (_ptr && !_cmp(tmp.first, _ptr->val.first)) {
						_ptr = _ptr->parent;
					}
					return (*this);
				}
			}

			rbtiterator operator++(int) {
				rbtiterator tmp(*this);
				++(*this);
				return (tmp);
			}

			rbtiterator & operator--(void) {
				if (!_ptr) {
					_ptr = _tree->root();
					while (_ptr->r) {
						_ptr = _ptr->r;
					}
					return (*this);
				}
				if (_ptr->l) {
					_ptr = _ptr->l;
					while (_ptr->r) {
						_ptr = _ptr->r;
					}
					return (*this);
				} else {
					value_type tmp = _ptr->val;
					while (_ptr && _cmp(tmp.first, _ptr->val.first)) {
						_ptr = _ptr->parent;
					}
					return (*this);
				}
			}

			rbtiterator operator--(int) {
				rbtiterator tmp(*this);
				--(*this);
				return (tmp);
			}

			operator rbtiterator<const T, cmp, ctnr>() const {
				return (rbtiterator<const T, cmp, ctnr>(this->_ptr, this->_tree));
			}

		protected:
			node	_ptr;
			const ctnr *	_tree;
			cmp		_cmp;
	};

	template <typename lit, typename rit, typename cmp, typename ctnr>
	bool operator==(const rbtiterator<lit, cmp, ctnr> & lhs, const rbtiterator<rit, cmp, ctnr> & rhs) {
		return (lhs.base() == rhs.base());
	}

	template <typename it, typename cmp, typename ctnr>
	bool operator==(const rbtiterator<it, cmp, ctnr> & lhs, const rbtiterator<it, cmp, ctnr> & rhs) {
		return (lhs.base() == rhs.base());
	}

	template <typename lit, typename rit, typename cmp, typename ctnr>
	bool operator!=(const rbtiterator<lit, cmp, ctnr> & lhs, const rbtiterator<rit, cmp, ctnr> & rhs) {
		return (lhs.base() != rhs.base());
	}

	template <typename it, typename cmp, typename ctnr>
	bool operator!=(const rbtiterator<it, cmp, ctnr> & lhs, const rbtiterator<it, cmp, ctnr> & rhs) {
		return (lhs.base() != rhs.base());
	}
}
