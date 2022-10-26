/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:09:37 by tnaton            #+#    #+#             */
/*   Updated: 2022/10/23 12:54:15 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vector.hpp"
#include <string>
#include <vector>

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
    for (ft::vector<int>::iterator it = container.begin(); it != container.end(); it++)
        std::cout << *it << ' ';
    std::cout << '\n';
}

int main () {
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
	{
		ft::vector<int> v(2, 400);

		std::cerr << "Capacity : " << v.capacity() << std::endl;

		v.insert(v.begin(), 5, 200);

		std::cerr << "Capacity : " << v.capacity() << std::endl;
	}
	/*
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
