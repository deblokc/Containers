/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:11:43 by tnaton            #+#    #+#             */
/*   Updated: 2022/12/01 18:48:57 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include "viterator.hpp"
# include "reverse_iterator.hpp"
# include <memory>
# include <iostream>
# include <limits>
# include "utils.hpp"

namespace ft {

	template <class T, class Allocator = std::allocator<T> > class vector {
		// definition des types
		public:
			typedef T													value_type;
			typedef Allocator											allocator_type;
			typedef typename Allocator::size_type						size_type;
			typedef typename Allocator::difference_type					difference_type;
			typedef typename Allocator::reference						reference;
			typedef typename Allocator::const_reference					const_reference;
			typedef typename Allocator::pointer							pointer;
			typedef typename Allocator::const_pointer					const_pointer;
			typedef typename ft::viterator<pointer, vector>				iterator;
			typedef typename ft::viterator<const_pointer, vector>		const_iterator;
			typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;


		// definition des constructeurs
		public:
			explicit vector(const allocator_type& alloc = allocator_type()){
				_alloc = alloc;
				_start = NULL;
				_end = NULL;
				_capacity = 0;
				_size = 0;
			}

			explicit vector(size_type count, const value_type& value = value_type(), \
					const allocator_type& alloc = Allocator()) {
				_alloc = alloc;
				_capacity = count;
				if (count > _alloc.max_size())
					throw(std::length_error("Over max size"));
				if (count)
					_start = _alloc.allocate(_capacity);
				else
					_start = NULL;
				_end = _start;
				for (size_type i = 0; i < _capacity; i++){
					_alloc.construct(_end, value);
					_end++;
				}
				_size = count;
			}

			template <class InputIt> vector(InputIt first, InputIt last, \
					const Allocator& alloc = Allocator(),
					typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL) : _alloc(alloc){
				_alloc = alloc;
				_size = 0;
				_start = NULL;
				_end = NULL;
				_capacity = 0;
				this->assign(first, last);
			}

			vector(const vector& other){
				_size = 0;
				_start = NULL;
				_end = NULL;
				_capacity = 0;
				_alloc = other._alloc;
				this->assign(other._start, other._end);
			}

			// definition du destructeur
			~vector(void){
				this->clear();
				if (_capacity)
					_alloc.deallocate(_start, _capacity);
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
				typedef typename iterator_traits<InputIt>::iterator_category	category;
				_assign(first, last, category());
			}

		private:
			template<class InputIt>
			void _assign(InputIt first, InputIt last, std::random_access_iterator_tag) {
				if (static_cast<size_type>(last - first) > _alloc.max_size())
					throw (std::length_error("Over max size"));
				this->clear();
				if (static_cast<size_type>(last - first) > _capacity) {
					if (_capacity)
						_alloc.deallocate(_start, _capacity);
					_capacity = last - first;
					if (_capacity)
						_start = _alloc.allocate(_capacity);
					_end = _start;
					while (first != last) {
						_alloc.construct(_end, *first);
						first++;
						_end++;
					}
					_size = _capacity;
				} else {
					pointer	tmp = _start;
					for (; first != last; tmp++, first++, _size++) {
						_alloc.construct(tmp, *first);
					}
					_end = tmp;
				}
			}

			template<class InputIt>
			void _assign(InputIt first, InputIt last, std::input_iterator_tag) {
				this->clear();
				while (first != last) {
					this->push_back(*first);
					first++;
				}
			}

		public:
			void assign(size_type count, const value_type & value) {
				if (count > _alloc.max_size())
					throw (std::length_error("Over max size"));
				this->clear();
				if (count > _capacity)
				{
					if (_capacity)
						_alloc.deallocate(_start, _capacity);
					_start = _alloc.allocate(count);
					_capacity = count;
				}
				_size = count;
				_end = _start;
				while (count--) {
					_alloc.construct(_end, value);
					_end++;
				}
			}

			void reserve(size_type new_cap) {
				if (new_cap > _alloc.max_size()) {
					throw (std::length_error("Over max size"));
				}
				if (!_capacity)
					return ;
				if (new_cap > _capacity) {
					pointer new_start = _alloc.allocate(new_cap);
					pointer new_end = new_start;
					pointer tmp = _start;

					while (tmp != _end) {
						_alloc.construct(new_end, *tmp);
						new_end++;
						tmp++;
					}
					size_type exsize = _size;
					this->clear();
					_size = exsize;
					_alloc.deallocate(_start, _capacity);
					_capacity = new_cap;
					_start = new_start;
					_end = new_end;
				}
			}

			void resize(size_type count, T value = T()) {
				if (count > _alloc.max_size()) {
					throw (std::length_error("Over max size"));
				}
				if (_size > count) {
					pointer new_start = NULL;
					if (count)
						new_start = _alloc.allocate(count);
					pointer new_end = new_start;
					pointer tmp = _start;

					for (size_type i = 0; i < count; i++) {
						_alloc.construct(new_end, *tmp);
						tmp++;
						new_end++;
					}
					this->clear();
					_size = count;
					if (_start)
						_alloc.deallocate(_start, _capacity);
					_capacity = count;
					_start = new_start;
					_end = new_end;
				} else if (_size < count) {
					pointer new_start = _alloc.allocate(count);
					pointer new_end = new_start;
					pointer tmp = _start;

					while (tmp != _end) {
						_alloc.construct(new_end, *tmp);
						tmp++;
						new_end++;
					}
					for (size_type i = _size; i < count; i++) {
						_alloc.construct(new_end, value);
						new_end++;
					}
					this->clear();
					_size = count;
					if (_capacity)
						_alloc.deallocate(_start, _capacity);
					_capacity = count;
					_start = new_start;
					_end = new_end;
				}
			}

			void push_back(const T& value) {
				if (_size + 1 > _alloc.max_size())
					throw (std::length_error("Over max size"));
				if (!_capacity) {
					_capacity = 1;
					_start = _alloc.allocate(_capacity);
					_end = _start;
					_alloc.construct(_end, value);
					_end++;
					_size = 1;
				} else if (_size == _capacity) {
					pointer new_start = _alloc.allocate(_capacity * 2);
					pointer new_end = new_start;
					pointer tmp = _start;
					size_type new_size = 0;

					for (size_type i = 0; i < _size; i++) {
						_alloc.construct(new_end, *tmp);
						new_end++;
						tmp++;
						new_size++;
					}
					this->clear();
					_alloc.construct(new_end, value);
					_size = new_size + 1;
					_alloc.deallocate(_start, _capacity);
					_capacity *= 2;
					_start = new_start;
					_end = new_end + 1;
				} else {
					_alloc.construct(_end, value);
					_end++;
					_size++;
				}
			}

			void pop_back(void) {
				_alloc.destroy(_end - 1);
				_end--;
				_size--;
			}

			iterator erase(iterator pos) {
				if (pos == end())
					return (end());
				if (pos + 1 != end()) {
					_copy(pos + 1, end(), pos);
				}
				--_end;
				_alloc.destroy(_end);
				_size--;
				return iterator(pos);
			}

			iterator erase(iterator first, iterator last) {
				if (first != last) {
					if (last != end()) {
						_copy(last, end(), first);
						pointer new_end = &(*first) + (end() - last);
						_clear(new_end, _end - new_end);
						_size -= (last - first);
						_end = new_end;
						return iterator(first);
					}
					else {
						pointer new_end = &(*first) + (end() - last);
						_clear(new_end, _end - new_end);
						_size -= (last - first);
						_end = new_end;
						return iterator(_end);
					}
				}
				return iterator(last);
			}

		private:
			template<class InputIt, class OutputIt>
			OutputIt _copy(InputIt first, InputIt last,
						  OutputIt d_first)
			{
				for (; first != last; (void)++first, (void)++d_first) {
					*d_first = *first;
				}
				return d_first;
			}

		public:
			iterator insert(iterator pos, const T& value) {
				if (_size + 1 > _alloc.max_size())
					throw (std::length_error("Over max size"));
				if (!_capacity) {
					push_back(value);
					return iterator(_start);
				} else {
					if (_size == _capacity) {
						pointer new_start = _alloc.allocate(_capacity * 2);
						pointer new_end = new_start;
						pointer tmp = _start;

						while (tmp != &(*pos)) {
							_alloc.construct(new_end, *tmp);
							new_end++;
							tmp++;
						}
						_alloc.construct(new_end, value);
						iterator ret(new_end);
						new_end++;
						while (tmp != _end) {
							_alloc.construct(new_end, *tmp);
							tmp++;
							new_end++;
						}
						size_type exsize = _size;
						this->clear();
						_size = exsize + 1;
						_alloc.deallocate(_start, _capacity);
						_capacity *= 2;
						_start = new_start;
						_end = new_end;
						return (ret);
					} else {
						if (pos.base() != _end) {
							_alloc.construct(_end, *(_end - 1));
							pointer tmp = (_end - 1);
							while (tmp != &(*pos)) {
								*(tmp + 1) = *tmp;
								tmp--;
							}
							*(tmp + 1) = *pos;
							*pos = value;
							_size += 1;
							_end = _start + _size;
						} else {
							_alloc.construct(_end, value);
							_end++;
							_size++;
						}
					}
				}
				return iterator(pos);
			}
	

			iterator insert(iterator pos, size_type count, const T& value) {
				if (_size + count > _alloc.max_size())
					throw (std::length_error("Over max size"));
				if (!_size) {
					assign(count, value);
				} else if (_size + count <= _capacity) {
					if (pos == end()) {
						for (; count; count--) {
							push_back(value);
						}
					} else { 
						pointer tmp_end = _end - 1;
						pointer new_end = _end + count - 1;
						for (; tmp_end != pos.base(); --new_end, --tmp_end) {
							_alloc.construct(new_end, *tmp_end);
						}
						_alloc.construct(new_end, *tmp_end);
						pointer tmp = pos.base();
						for (; count; count--, tmp++, _size++, _end++) {
							_alloc.construct(tmp, value);
						}
						//for (size_type i = 0; i < count; i++) {
						//	pos = insert(pos, value);
						//}
					}
				} else if (_size + count <= _capacity * 2) {
					for (size_type i = 0; i < count; i++) {
						pos = insert(pos, value);
					}
				} else {
					pointer new_start = _alloc.allocate(_size + count);
					pointer new_end = new_start;
					pointer tmp = _start;

					while (tmp != &(*pos)) {
						_alloc.construct(new_end, *tmp);
						new_end++;
						tmp++;
					}
					iterator ret(new_end);
					for (size_type i = 0; i < count; i++) {
						_alloc.construct(new_end, value);
						new_end++;
					}
					while (tmp != _end) {
						_alloc.construct(new_end, *tmp);
						tmp++;
						new_end++;
					}
					size_type exsize = _size;
					this->clear();
					_size = exsize + count;
					_alloc.deallocate(_start, _capacity);
					_capacity = _size;
					_start = new_start;
					_end = new_end;
					return (ret);
				}
				return iterator(pos);
			}

			template<class InputIt>
			iterator insert(iterator pos, InputIt first, InputIt last,
					typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL) {
				typedef typename iterator_traits<InputIt>::iterator_category	category;
				if (!_capacity) {
					assign(first, last);
					return iterator(_start);
				}
				return iterator(_insert_range(pos, first, last, category()));
			}

		private:
			template<class InputIt>
			iterator _insert_range(iterator pos, InputIt first, InputIt last, std::input_iterator_tag) {
				vector tmp(first, last);
				return iterator(_insert_range(pos, tmp.begin(), tmp.end(), std::random_access_iterator_tag()));
			}

			template<class InputIt>
			iterator _insert_range(iterator pos, InputIt first, InputIt last, std::random_access_iterator_tag) {
				if (first == last)
					return pos;
				size_type	dist = last - first;
				if (_size + dist > _alloc.max_size())
					throw (std::length_error("Over max size"));
				if (!_size) {
					assign(first, last);
					return iterator(_start);
				}
				InputIt	tmpIt = first;
				if (_size + dist <= _capacity) {
					if (pos == end()) {
						for (; first != last; first++) {
							push_back(*first);
						}
					} else {
						pointer tmp_end = _end - 1;
						pointer new_end = _end + dist - 1;
						for (; tmp_end != pos.base(); --new_end, --tmp_end) {
							_alloc.construct(new_end, *tmp_end);
						}
						_alloc.construct(new_end, *tmp_end);
						pointer tmp = pos.base();
						for (; first != last; tmp++, first++) {
							_alloc.construct(tmp, *first);
						}
						_end += dist;
						_size += dist;
					}
				} else if (_size + dist <= _capacity * 2) {
					pointer new_start = _alloc.allocate(_capacity * 2);
					pointer tmp = new_start;
					pointer old_tmp = _start;
					for (; old_tmp != pos.base(); tmp++, old_tmp++) {
						_alloc.construct(tmp, *old_tmp);
					}
					for (; first != last; first++, tmp++) {
						_alloc.construct(tmp, *first);
					}
					for (; old_tmp != _end; tmp++, old_tmp++) {
						_alloc.construct(tmp, *old_tmp);
					}
					old_tmp = _start;
					for (; old_tmp != _end; old_tmp++) {
						_alloc.destroy(old_tmp);
					}
					if (_capacity)
						_alloc.deallocate(_start, _capacity);
					_start = new_start;
					_end = tmp;
					_capacity *= 2;
					_size = _end - _start;
				} else {
					pointer new_start = _alloc.allocate(_size + dist);
					pointer new_end = new_start;
					pointer tmp = _start;

					while (tmp != &(*pos)) {
						_alloc.construct(new_end, *tmp);
						new_end++;
						tmp++;
					}
					iterator ret(new_end);
					for (size_type i = 0; i < dist; i++) {
						_alloc.construct(new_end, *tmpIt);
						new_end++;
						tmpIt++;
					}
					while (tmp != _end) {
						_alloc.construct(new_end, *tmp);
						tmp++;
						new_end++;
					}
					size_type exsize = _size;
					this->clear();
					_size = exsize + dist;
					_alloc.deallocate(_start, _capacity);
					_capacity = _size;
					_start = new_start;
					_end = new_end;
					return (ret);
				}
				return iterator(pos);
			}

		public:
			void swap(vector & other) {
				ft::swap(this->_start, other._start);
				ft::swap(this->_end, other._end);
				ft::swap(this->_capacity, other._capacity);
				ft::swap(this->_size, other._size);
				ft::swap(this->_alloc, other._alloc);
			}

			iterator begin(void) {
				return iterator(_start);
			}

			const_iterator begin(void) const {
				return const_iterator(_start);
			}

			reverse_iterator rbegin(void) {
				return (reverse_iterator(this->end()));
			}

			const_reverse_iterator rbegin(void) const {
				return (const_reverse_iterator(this->end()));
			}

			iterator end(void) {
				return iterator(_end);
			}

			const_iterator end(void) const {
				return const_iterator(_end);
			}

			reverse_iterator rend(void) {
				return (reverse_iterator(this->begin()));
			}

			const_reverse_iterator rend(void) const {
				return (const_reverse_iterator(this->begin()));
			}

			void clear(void) {
				for (size_type i = 0; i < _size; i++) {
					_end--;
					_alloc.destroy(_end);
				}
				_size = 0;
			}

		private:
			void _clear(pointer start, size_type size) {
				for (size_type i = 0; i < size; i++) {
					_alloc.destroy(start);
					start++;
				}
			}

			template<class InputIt, class OutputIt>
			OutputIt _revcopy(InputIt first, InputIt last, OutputIt d_last) {
				for (; first != last; (void)--last, (void)--d_last) {
					*d_last = *last;
				}
				return (d_last);
			}

		public:
			reference at(size_type pos) {
				if (pos >= _size)
					throw (std::out_of_range("ft::vector"));
				return (*(_start + pos));
			}

			const_reference at(size_type pos) const {
				if (pos >= _size)
					throw (std::out_of_range("ft::vector"));
				return (*(_start + pos));
			}

			reference front(void) {
				return (*this->begin());
			}

			const_reference front(void) const {
				return (*this->begin());
			}

			reference back(void) {
				return (*(this->end() - 1));
			}

			const_reference back(void) const {
				return (*(this->end() - 1));
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
					this->assign(other._start, other._end);
					return (*this);
				}

		private:
			pointer			_start;
			pointer			_end;
			allocator_type	_alloc;
			size_type		_size;
			size_type		_capacity;
	};

	template<class T, class Alloc>
	bool operator==(const ft::vector<T, Alloc> & lhs, const ft::vector<T, Alloc> & rhs) {
		return ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template<class T, class Alloc>
	bool operator!=(const ft::vector<T, Alloc> & lhs, const ft::vector<T, Alloc> & rhs) {
		return ((lhs.size() != rhs.size()) || !ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template<class T, class Alloc>
	bool operator<(const ft::vector<T, Alloc> & lhs, const ft::vector<T, Alloc> & rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class T, class Alloc>
	bool operator>(const ft::vector<T, Alloc> & lhs, const ft::vector<T, Alloc> & rhs) {
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template<class T, class Alloc>
	bool operator<=(const ft::vector<T, Alloc> & lhs, const ft::vector<T, Alloc> & rhs) {
		return (!(lhs > rhs));
	}

	template<class T, class Alloc>
	bool operator>=(const ft::vector<T, Alloc> & lhs, const ft::vector<T, Alloc> & rhs) {
		return (!(lhs < rhs));
	}
	template<class T, class Alloc>
	void swap(ft::vector<T, Alloc> & lhs, ft::vector<T, Alloc> & rhs) {
		lhs.swap(rhs);
	}
}

#endif
