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

	template <typename T, typename ctnr>
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
			explicit rbtiterator(const node & other_ptr): _ptr(other_ptr) {}

			template <typename Ptr>
			rbtiterator(const rbtiterator<Ptr, typename enable_if<is_same<Ptr, typename ctnr::pointer>::val, ctnr>::type> & other) : _ptr(other.base()) {}

			~rbtiterator() {
			}

			rbtiterator & operator=(const rbtiterator & other) {
				if (this == &other)
					return (*this);
				this->_ptr = other._ptr;
				return (*this);
			}

			const node base(void) const {return _ptr;}
			reference operator*(void) const {return (*_ptr->val);}
			pointer operator->(void) {return &(*_ptr->val);}
			pointer operator->(void) const {return &(*_ptr->val);}

			rbtiterator & operator++(void) {
				if (!_ptr->val) {
					_ptr = _ptr->parent;
					while (_ptr->l) {
						_ptr = _ptr->l;
					}
					return (*this);
				}
				if (_ptr->r) {
					_ptr = _ptr->r;
					while (_ptr->l) {
						_ptr = _ptr->l;
					}
					return (*this);
				} else {
					while (_ptr->parent->val && _ptr->parent->r == _ptr) {
						_ptr = _ptr->parent;
					}
					_ptr = _ptr->parent;
					return (*this);
				}
			}

			rbtiterator operator++(int) {
				rbtiterator tmp(*this);
				++(*this);
				return (tmp);
			}

			rbtiterator & operator--(void) {
				if (!_ptr->val) {
					_ptr = _ptr->parent;
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
					while (_ptr->parent->val && _ptr->parent->l == _ptr) {
						_ptr = _ptr->parent;
					}
					_ptr = _ptr->parent;
					return (*this);
				}
			}

			rbtiterator operator--(int) {
				rbtiterator tmp(*this);
				--(*this);
				return (tmp);
			}

			operator rbtiterator<const T, ctnr>() const {
				return (rbtiterator<const T, ctnr>(this->_ptr));
			}

		protected:
			node			_ptr;
	};

	template <typename lit, typename rit, typename ctnr>
	bool operator==(const rbtiterator<lit, ctnr> & lhs, const rbtiterator<rit, ctnr> & rhs) {
		return (lhs.base() == rhs.base());
	}

	template <typename it, typename ctnr>
	bool operator==(const rbtiterator<it, ctnr> & lhs, const rbtiterator<it, ctnr> & rhs) {
		return (lhs.base() == rhs.base());
	}

	template <typename lit, typename rit, typename ctnr>
	bool operator!=(const rbtiterator<lit, ctnr> & lhs, const rbtiterator<rit, ctnr> & rhs) {
		return (lhs.base() != rhs.base());
	}

	template <typename it, typename ctnr>
	bool operator!=(const rbtiterator<it, ctnr> & lhs, const rbtiterator<it, ctnr> & rhs) {
		return (lhs.base() != rhs.base());
	}
}
