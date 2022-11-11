/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:11:39 by tnaton            #+#    #+#             */
/*   Updated: 2022/11/10 15:19:53 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
# include <vector>
# include "vector.hpp"

namespace ft {
	template <class T, class Container = std::vector<T> > class stack {
		public:
			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;
			explicit stack( const Container& cont = Container() ): c(cont) {};
			stack( const stack& other ) : c(other.c) {};
			~stack() {};
			stack& operator=( const stack& other ) {if(this==&other){return *this;}this->c = other.c;return *this;};
			reference top() {return this->c.back();};
			const_reference top() const {return this->c.back();};
			bool empty() const {return this->c.empty();};
			size_type size() const {return this->c.size();};
			void push(const value_type & value){this->c.push_back(value);};
			void pop(){this->c.pop_back();};
			bool friend operator==(const stack& lhs, const stack& rhs){return lhs.c == rhs.c;};
			bool friend operator!=(const stack& lhs, const stack& rhs){return lhs.c != rhs.c;};
			bool friend operator<(const stack& lhs, const stack& rhs){return lhs.c < rhs.c;};
			bool friend operator<=(const stack& lhs, const stack& rhs){return lhs.c <= rhs.c;};
			bool friend operator>(const stack& lhs, const stack& rhs){return lhs.c > rhs.c;};
			bool friend operator>=(const stack& lhs, const stack& rhs){return lhs.c >= rhs.c;};
		protected:
			container_type c;
	};
}
#endif
