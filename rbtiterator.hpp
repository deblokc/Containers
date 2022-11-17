/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtiterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:07:10 by tnaton            #+#    #+#             */
/*   Updated: 2022/11/17 19:37:21 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iterator_traits.hpp"
#include "utils.hpp"

namespace ft {

	template <typename ptr, typename ctnr>
	class rbtiterator {
		public:
			typedef ptr									iterator_type;
			typedef std::bidirectional_iterator_tag		iterator_category;
			typedef typename ctnr::value_type			value_type;
			typedef typename ctnr::difference_type		difference_type;
			typedef typename ctnr::reference			reference;
			typedef typename ctnr::pointer				pointer;

			rbtiterator(void): _ptr() {}
			explicit rbtiterator(const iterator_type & other_ptr): _ptr(other_ptr) {}

			template <typename Ptr>
			rbtiterator(const rbtiterator<Ptr, typename enable_if<is_same<Ptr, typename ctnr::pointer>::val, ctnr>::type> & other) : _ptr(other.base()) {}

			~rbtiterator() {}

			rbtiterator & operator=(const rbtiterator & other) {
				if (this == &other)
					return (*this);
				this->_ptr = other._ptr;
				return (*this);
			}

			const iterator_type & base(void) const {return _ptr;}
			reference operator*(void) const {return *_ptr;}
			pointer operator->(void) const {return _ptr;}

		protected:
			iterator_type	_ptr;
	};
}
