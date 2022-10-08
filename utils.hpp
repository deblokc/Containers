#ifndef UTILS_HPP
# define UTILS_HPP

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
}

#endif
