/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:09:37 by tnaton            #+#    #+#             */
/*   Updated: 2022/11/14 11:11:29 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include "vector.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <sys/time.h>
#define NAMESPACE std

class	Clock {
	public:
		Clock(void) {gettimeofday(&_time, NULL);};
		long time(void) {struct timeval now; gettimeofday(&now, NULL); return (((now.tv_sec * 1000) - (_time.tv_sec * 1000)) + (now.tv_usec / 1000) - (_time.tv_usec / 1000));}
	private:
		struct timeval _time;
};

/*
template<class T>
void print(T& vector) {
	typedef typename T::iterator iterator;
	for (iterator tmp = vector.begin(); tmp != vector.end(); tmp++) {
		std::cout << *tmp << " ";
	}
	std::cout << std::endl;
}

template<class T>
void printeq(T& v1, T& v2) {
	if (v1 == v2)
		std::cout << "Equal" << std::endl;
	else
		std::cout << "Not Equal" << std::endl;
}

void print(int id, const ft::vector<int>& container)
{
    std::cout << id << ". ";
    for (ft::vector<int>::const_iterator it = container.begin(); it != container.end(); it++)
        std::cout << *it << ' ';
    std::cout << '\n';
}
*/

int main () {

	Clock test;

	{
		for (int i = 0; i < 1000; i++) {
			NAMESPACE::vector<int> v1(100000, 1);
			NAMESPACE::vector<int> v2(100000, 2);
			NAMESPACE::vector<int> v3(100000, 3);
			NAMESPACE::vector<int> v4(100000, 4);
			NAMESPACE::vector<int> v5(100000, 5);
			NAMESPACE::vector<int> v6(100000, 6);
			NAMESPACE::vector<int> v7(100000, 7);
			NAMESPACE::vector<int> v8(100000, 8);
			NAMESPACE::vector<int> v9(100000, 9);
			std::cout << i/10 << "." << i%10 << "%" << std::flush << '\r';
			std::cout.clear();
		}
	}
	long	tmp = test.time();

	std::cout << tmp/1000 << "." << tmp%1000 << "s" << std::endl;
/*
	{
		ft::vector<int> v;

		ft::vector<int>::iterator it = v.insert(v.end(), 4);
		
		std::cerr << "capa : " << v.capacity() << " | size : " << v.size() << std::endl;

		std::cerr << "Val : " << *it << std::endl;
	}
*/
/*	{
		ft::vector<int> c1(3, 100);
		print(1, c1);
	
		ft::vector<int>::iterator it = c1.begin();
		it = c1.insert(it, 200);
		print(2, c1);
	 
		c1.insert(it, 2, 300);
		print(3, c1);
	 
		// `it` no longer valid, get a new one:
		it = c1.begin();
	 
		ft::vector<int> c2(2, 400);
		c1.insert(it + 2, c2.begin(), c2.end());
		print(4, c1);
	 
		int arr[] = {501, 502, 503};
		c1.insert(c1.begin(), arr, arr + 3);
		print(5, c1);
 
	}
*/
/*	{
		ft::vector<int> ft(4, 400);
		std::vector<int> std(4, 400);

		std::cerr << "std capacity : " << std.capacity() << std::endl;
		std::cerr << "ft capacity : " << ft.capacity() << std::endl;

		std.insert(std.begin(), 3, 200);
		ft.insert(ft.begin(), 3, 200);

		std::cerr << "std capacity : " << std.capacity() << std::endl;
		std::cerr << "ft capacity : " << ft.capacity() << std::endl;
	}
*/	/*
	{
		ft::vector<int> b(37, 1);

		b.erase(b.begin() + 1, b.begin() + 2);

		b.erase(b.begin(), b.end());

		print(b);
	}*/
	/*
	{
		ft::vector<double> test;
		ft::vector<double> test2;

		printeq(test, test2);
	}
	{
		ft::vector<int> test(5, 42);
		ft::vector<int> test2;

		printeq(test, test2);
	}*/
/*
	{
		ft::vector<double> test;
		
		for (int i = 0; i < 32; i++) {
			test.push_back(i);
		}
		std::cout << "Pushed " << test.size() << " elements in test" << std::endl;

		print(test);

		test.push_back(42);

		std::cout << "Added 42" << std::endl;

		print(test);

		test.assign(test.begin(), test.begin() + 21);

		print(test);
	}*/
}
