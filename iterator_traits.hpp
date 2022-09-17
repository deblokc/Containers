#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP
#endif

namespace ft {
	template<class Iter> struct iterator_traits {
		typename typedef Iter::difference_type		difference_type;
		typename typedef Iter::value_type			value_type;
		typename typedef Iter::pointer				pointer;
		typename typedef Iter::reference			reference;
		typename typedef Iter::iterator_category	iterator_category;
	};

	template<class T> struct iterator_traits<T*> {
		typename typedef std::ptrdiff_t						difference_type;
		typename typedef T									value_type;
		typename typedef T*									pointer;
		typename typedef T&									reference;
		typename typedef std::random_access_iterator_tag	iterator_category;
	};
}
