/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:09:37 by tnaton            #+#    #+#             */
/*   Updated: 2022/10/08 18:02:27 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vector.hpp"
#include <string>
#include <vector>

int main () {
	std::vector<int> test;

	std::cout << "size : " << test.size() << std::endl;
	std::cout << "capacity : " << test.capacity() << std::endl;

	for (int i = 0; i < 20; i++) {
		test.push_back(i);
		std::cout << "size : " << test.size() << std::endl;
		std::cout << "capacity : " << test.capacity() << std::endl;
	}
}
