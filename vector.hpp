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

	template<bool, class T = void>
	struct	enable_if {};

	template<class T>
	struct	enable_if<true, T> { typedef T type; };

	template<bool is_integral, typename T>
	struct	is_integral_test {
		typedef T type;
		static const bool value = is_integral;
	};

	template <typename>
		struct is_integral_type : is_integral_test<false, bool> {};

	template <>
		struct is_integral_type<bool> : is_integral_test<true, bool> {};

	template <>
		struct is_integral_type<char> : is_integral_test<true, char> {};
	
	template <>
		struct is_integral_type<signed char> : is_integral_test<true, signed char> {};
	
	template <>
		struct is_integral_type<unsigned char> : is_integral_test<true, unsigned char> {};
	
	template <>
		struct is_integral_type<short int> : is_integral_test<true, short int> {};
	
	template <>
		struct is_integral_type<unsigned short int> : is_integral_test<true, unsigned short int> {};
	
	template <>
		struct is_integral_type<int> : is_integral_test<true, int> {};
	
	template <>
		struct is_integral_type<unsigned int> : is_integral_test<true, unsigned int> {};
	
	template <>
		struct is_integral_type<long int> : is_integral_test<true, long int> {};
	
	template <>
		struct is_integral_type<unsigned long int> : is_integral_test<true, unsigned long int> {};

	template <typename T>
		struct is_integral : is_integral_type<T> {};

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
			typedef typename ft::Iterator<T>			const_iterator;

		// definition des constructeurs
		public:
			explicit vector(const allocator_type& alloc = allocator_type()){
				_alloc = alloc;
				_start = NULL;
				_end = NULL;
				_cap_end = NULL;
				_capacity = 0;
				_size = 0;
			//	std::cout << "vector default/alloc constructor" << std::endl;
			}

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
			//	std::cout << "vector xval constructor" << std::endl;
			}

			template <class InputIt> vector(InputIt first, InputIt last, \
					const Allocator& alloc = Allocator(),
					typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type = NULL){
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
					_alloc.construct(_end, *first);
					first++;
					_end++;
				}
				_size = _capacity;
				_cap_end = _start + _capacity;
			//	std::cout << "vector input constructor" << std::endl;
			}

			vector(const vector& other){
				_alloc = other._alloc;
				_start = other._start;
				_end = other._end;
				_cap_end = other._end;
				_capacity = other._capacity;
			//	std::cout << "vector copy constructor" << std::endl;
			}

			// definition du destructeur
			~vector(void){
				this->clear();
				_alloc.deallocate(_start, _capacity);
			//	std::cout << "vector destructor" << std::endl;
			}

			// definition des fonctions membres
		public:

			bool empty(void) const {
				return ((_size == 0) ? true : false);
			}

			size_type size(void) const {
				return (_size);
			}

			size_type max_size(void) const {
				return (_alloc.max_size());
			}

			size_type capacity(void) const {
				return (_capacity);
			}

			allocator_type get_allocator(void) const {
				return (_alloc);
			}

			template< class InputIt >
			void assign(InputIt first, InputIt last,
			typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL) {
				this->clear();
				if (_start)
					_alloc.deallocate(_start, _capacity);
				_capacity = 0;
				InputIt tmp = first;
				while (tmp != last){
					tmp++;
					_capacity++;
				}
				_start = _alloc.allocate(_capacity);
				_end = _start;
				while (first != last) {
					_alloc.construct(_end, *first);
					first++;
					_end++;
				}
				_size = _capacity;
				_cap_end = _start + _capacity;
			}

			void assign(size_type count, const value_type & value) {
				this->clear();
				if (_start)
					_alloc.deallocate(_start, _capacity);
				_capacity = 0;
				_start = _alloc.allocate(count);
				_capacity = count;
				_size = count;
				_end = _start;
				while (count--) {
					_alloc.construct(_end, value);
					_end++;
				}
				_cap_end = _start + _capacity;
			}

			iterator begin(void) {
				return (_start);
			}

			const_iterator begin(void) const {
				return (_start);
			}

			iterator end(void) {
				return (_end);
			}

			const_iterator end(void) const {
				return (_end);
			}

			void clear(void) {
				for (size_type i = 0; i < _size; i++) {
					_end--;
					_alloc.destroy(_end);
				}
			}

			reference at(size_type pos) {
				if (pos >= size())
					throw (std::out_of_range("ft::vector"));
				return (_start + pos);
			}

			const_reference at(size_type pos) const {
				if (pos >= size())
					throw (std::out_of_range("ft::vector"));
				return (_start + pos);
			}

			reference front(void) {
				return (this->begin());
			}

			const_reference front(void) const {
				return (this->begin());
			}

			reference back(void) {
				return (this->end() - 1);
			}

			const_reference back(void) const {
				return (this->end() - 1);
			}

			// definition des surcharges d'operateurs
		public:
				value_type & operator[](size_type i) const {
				pointer tmp = _start;
				while (i--)
					tmp++;
				return (*tmp);
			}

				vector & operator=(const vector & other) {
					if (this == &other)
						return (*this);
					_alloc = other._alloc;
					_start = other._start;
					_end = other._end;
					_cap_end = other._end;
					_capacity = other._capacity;
					return (*this);
				}

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
