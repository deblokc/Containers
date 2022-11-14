/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:09:37 by tnaton            #+#    #+#             */
/*   Updated: 2022/11/14 19:37:17 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <sys/time.h>

#ifndef NAMESPACE
# define NAMESPACE std
#endif

#ifndef PREC
# define PREC 1
#endif

class	Clock {
	public:
		Clock(void) {gettimeofday(&_time, NULL);};
		long time(void) {struct timeval now; gettimeofday(&now, NULL); return (((now.tv_sec * 1000) - (_time.tv_sec * 1000)) + (now.tv_usec / 1000) - (_time.tv_usec / 1000));}
		void p(void) {long tmp = time(); std::cout << tmp/1000 << "." << tmp%1000 << "s" << std::endl;}
	private:
		struct timeval _time;
};

int main () {
	{
		std::cerr << "THIS IS PREC : " << PREC << std::endl;
		std::cout << "### TEST CONSTRUCTOR VECTOR ###" << std::endl;
		{
			Clock test;
			for (int i = 0; i < 10000 * PREC; i++) {
				for (int j = 0; j < 5000; j++)
					NAMESPACE::vector<std::string> v;
				std::cerr << i/(100 * PREC) << "." << i%(100 * PREC) << "%" << std::flush << '\r';
				std::cout.clear();
			}
			test.p();
		}
		std::cerr << std::endl;
		{
			Clock test;
			for (int i = 0; i < 1000 * PREC; i++) {
				NAMESPACE::vector<int> v1(100000, 1);
				NAMESPACE::vector<int> v2(100000, 2);
				NAMESPACE::vector<int> v3(100000, 3);
				NAMESPACE::vector<int> v4(100000, 4);
				NAMESPACE::vector<int> v5(100000, 5);
				NAMESPACE::vector<int> v6(100000, 6);
				NAMESPACE::vector<int> v7(100000, 7);
				NAMESPACE::vector<int> v8(100000, 8);
				NAMESPACE::vector<int> v9(100000, 9);
				std::cerr << i/(10 * PREC) << "." << i%(10 * PREC) << "%" << std::flush << '\r';
				std::cout.clear();
			}
			test.p();
		}
		std::cerr << std::endl;
		{
			std::string lst[1000];
			for (int i = 0; i < 1000; i++)
				lst[i] = "42";
			NAMESPACE::vector<std::string> vec(1000, "foo");
			Clock test;
			for (int i = 0; i < 10000 * PREC; i++) {
				NAMESPACE::vector<std::string> v1(lst, lst + 1000);
				NAMESPACE::vector<std::string> v2(lst, lst + 950);
				NAMESPACE::vector<std::string> v4(vec.begin(), vec.begin() + 900);
				NAMESPACE::vector<std::string> v5(lst, lst + 900);
				NAMESPACE::vector<std::string> v7(lst, lst + 500);
				NAMESPACE::vector<std::string> v8(lst, lst + 1000);
				NAMESPACE::vector<std::string> v9(vec.begin(), vec.end());

				std::cerr << i/(100 * PREC) << "." << i%(100 * PREC) << "%" << std::flush << '\r';
				std::cout.clear();
			}
			test.p();
		}
		std::cerr << std::endl;
		{
			Clock test;

			NAMESPACE::vector<std::string> v1(500, "bar");
			NAMESPACE::vector<NAMESPACE::vector<std::string> >v2 (2, v1);
			NAMESPACE::vector<NAMESPACE::vector<NAMESPACE::vector<std::string> > > v3(2, v2);
			for (int i = 0; i < 10000 * PREC; i++) {
				NAMESPACE::vector<NAMESPACE::vector<NAMESPACE::vector<std::string> > > vector1(v3);
				NAMESPACE::vector<NAMESPACE::vector<NAMESPACE::vector<std::string> > > vector2(v3);
				NAMESPACE::vector<NAMESPACE::vector<NAMESPACE::vector<std::string> > > vector3(v3);
				NAMESPACE::vector<NAMESPACE::vector<NAMESPACE::vector<std::string> > > vector4(v3);
				NAMESPACE::vector<NAMESPACE::vector<NAMESPACE::vector<std::string> > > vector5(v3);

				std::cerr << i/(100 * PREC) << "." << i%(100 * PREC) << "%" << std::flush << '\r';
				std::cout.clear();
			}
			test.p();
		}
		std::cerr << std::endl;
	}
	{
		std::cout << "### TEST OPERATOR= ###" << std::endl;
		{
			Clock test;

			NAMESPACE::vector<std::string> v1(5000, "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
			NAMESPACE::vector<std::string> v2;
			for (int i = 0; i < 5000 * PREC; i++) {
				v2 = v1;
				v1 = v2;
				std::cerr << i/(50 * PREC) << "." << i%(50 * PREC) << "%" << std::flush << '\r';
			}
			test.p();
		}
		std::cerr << std::endl;
	}
}
