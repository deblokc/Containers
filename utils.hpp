#ifndef UTILS_HPP
# define UTILS_HPP

#include "iterator_traits.hpp"

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
		struct is_integral : is_integral_type<typename remove_volatile_const<T>::type> {};

	template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
		for (; first1 != last1; ++first1, ++first2) {
			if (!(*first1 == *first2)) {
				return (false);
			}
		}
		return (true);
	}

	template<class InputIt1, class InputIt2, class BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
		for (; first1 != last1; ++first1, ++first2) {
			if (!p(*first1, *first2)) {
				return (false);
			}
		}
		return (true);
	}

	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
		for (; (first1 != last1) && (first2 != last2); ++first1, ++first2) {
			if (*first1 < *first2)
				return (true);
			if (*first1 > *first2)
				return (false);
		}
		return ((first1 == last1) && (first2 != last2));
	}

	template<class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp) {
		for (; (first1 != last1) && (first2 != last2); ++first1, ++first2) {
			if (comp(*first1, *first2))
				return (true);
			if (comp(*first2, *first1))
				return (false);
		}
		return ((first1 == last1) && (first2 != last2));
	}

	struct is_false {
		static const bool val = false;
		typedef is_false type;
	};

	struct is_true {
		static const bool val = true;
		typedef is_true type;
	};

	template<typename T, typename U>
	struct is_same : public is_false {};

	template<typename T>
	struct is_same<T, T> : public is_true {};

	template<typename ptr>
	void swap(ptr & lhs, ptr & rhs) {
		ptr tmp;
		tmp = rhs;
		rhs = lhs;
		lhs = tmp;
	}

}

#endif
