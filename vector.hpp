/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:11:43 by tnaton            #+#    #+#             */
/*   Updated: 2022/09/23 20:31:26 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include "iterator.hpp"
# include <memory>
# include <iostream>

namespace ft {
	template <class T, class Allocator = std::allocator<T> > class vector {
		// definition des types
		public:
			typedef T									value_type;
			typedef Allocator							allocator_type;
			typedef size_t								size_type;
			typedef std::ptrdiff_t						difference_type;
			typedef typename Allocator::reference		reference;
			typedef typename Allocator::const_reference	const_reference;
			typedef typename Allocator::pointer			pointer;
			typedef typename Allocator::const_pointer	const_pointer;
			typedef typename ft::Iterator<T>			iterator;

		// definition des constructeurs
		public:
			explicit vector(const allocator_type& alloc = allocator_type()){
				_alloc = alloc;
				_start = NULL;
				_end = NULL;
				_cap_end = NULL;
				_capacity = 0;
				_size = 0;
				std::cout << "vector default/alloc constructor" << std::endl;
			};

			explicit vector(size_type count, const value_type& value = value_type(), \
					const allocator_type& alloc = Allocator()) {
				_alloc = alloc;
				_capacity = count;
				_start = _alloc.allocate(_capacity);
				_end = _start;
				for (size_type i = 0; i < _capacity; i++){
					_alloc.construct(_end, value);
					_end++;
				}
				_cap_end = _start + count;
				_size = count;
				std::cout << "vector xval constructor" << std::endl;
			};

			template <class InputIt> vector(InputIt first, InputIt last, \
					const Allocator& alloc = Allocator()){
				InputIt tmp = first;
				_capacity = 0;
				while (tmp != last){
					tmp++;
					_capacity++;
				}
				_alloc = alloc;
				_start = _alloc.allocate(_capacity);
				_end = _start;
				while (first != last) {
					_alloc.construct(_end, first);
					first++;
					_end++;
				}
				_size = _capacity;
				_cap_end = _start + _capacity;
				std::cout << "vector input constructor" << std::endl;
			};

			vector(const vector& other){
				_alloc = other._alloc;
				_start = other._start;
				_end = other._end;
				_cap_end = other._end;
				_capacity = other._capacity;
				std::cout << "vector copy constructor" << std::endl;
			};

			// definition du destructeur
			~vector(void){
				if (_capacity)
					_alloc.deallocate(_start, _capacity);
				std::cout << "vector destructor" << std::endl;
			};

			// definition des fonctions membres
		public:
			size_type size(void) {
				return (_size);
			}

			void assign(size_type count, const value_type & value) {
				if (_capacity)
					_alloc.deallocate(_start, _capacity);
				_start = _alloc.allocate(count);
				_capacity = count;
				_size = count;
				_end = _start;
				while (count--) {
					_alloc.construct(_end, value);
					_end++;
				}
				_cap_end = _start + _capacity;
			};

			template< class InputIt >
			void assign(InputIt first, InputIt last){
				if (_capacity)
					_alloc.deallocate(_start, _capacity);
				InputIt tmp = first;
				while (tmp != last){
					tmp++;
					_capacity++;
				}
				_start = _alloc.allocate(_capacity);
				_end = _start;
				while (first != last) {
					_alloc.construct(_end, first);
					first++;
					_end++;
				}
				_size = _capacity;
				_cap_end = _start + _capacity;
			};

			iterator begin(void){
				return (_start);
			};

			iterator end(void){
				return (_end);
			}

			// definition des surcharges d'operateurs
		public:
				value_type & operator[](size_type i) const {
				pointer tmp = _start;
				while (i--)
					tmp++;
				return (*tmp);
			};

				vector & operator=(const vector & other) {
					_alloc = other._alloc;
					_start = other._start;
					_end = other._end;
					_cap_end = other._end;
					_capacity = other._capacity;
				};

		private:
			pointer			_start;
			pointer			_end;
			pointer			_cap_end;
			allocator_type	_alloc;
			size_type		_size;
			size_type		_capacity;
	};
}

#endif
