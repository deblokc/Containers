#ifndef ITERATOR_HPP
# define ITERATOR_HPP
#endif

namespace ft {
	template <class T, class Category = std::random_access_iterator_tag, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&> class Iterator {
		public:
			typedef Category	iterator_category;
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;

			Iterator(void){};
			Iterator(const Iterator & other){this->_ptr = other._ptr;};
			Iterator(pointer ptr){this->_ptr = ptr;};
			~Iterator(void){};
			Iterator &operator=(const Iterator & other){if (this != &other){this->_ptr = other._ptr;}return *this;};
			Iterator &operator++(void){this->_ptr++;return *this;};
			Iterator &operator++(int){Iterator tmp(*this);this->_ptr++;return tmp;};
			Iterator &operator--(void){this->_ptr--;return *this;};
			Iterator &operator--(int){Iterator tmp(*this);this->_ptr--;return tmp;};
			value_type &operator*(void){return *(this->_ptr);};
			value_type *operator->(void){return this->_ptr;};
			Iterator &operator+=(difference_type n){this->_ptr += n; return *this;};
			Iterator &operator-=(difference_type n){this->_ptr -= n; return *this;};
			Iterator operator+(difference_type n){Iterator tmp(*this); tmp += n; return (tmp);};
			Iterator operator-(difference_type n){Iterator tmp(*this); tmp -= n; return (tmp);};
			bool operator==(const Iterator & other){return this->_ptr == other._ptr;};
			bool operator!=(const Iterator & other){return this->_ptr != other._ptr;};
			bool operator>(const Iterator & other){return this->_ptr > other._ptr;};
			bool operator>=(const Iterator & other){return this->_ptr >= other._ptr;};
			bool operator<(const Iterator & other){return this->_ptr < other._ptr;};
			bool operator<=(const Iterator & other){return this->_ptr <= other._ptr;};
		private:
			pointer _ptr;
	};
	friend Iterator operator+(typename Iterator::difference_type n, Iterator i){return (i + n);};
	friend Iterator operator-(typename Iterator::difference_type n, Iterator i){return (i - n);};
}
