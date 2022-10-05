/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:09:37 by tnaton            #+#    #+#             */
/*   Updated: 2022/09/23 20:23:40 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vector.hpp"

int main () {
	int list[] = {'0', '1', '2', '3'};
	ft::vector<int> def;
	ft::vector<int> copy(def);
	ft::vector<char> xval(10, 'c');
	ft::vector<int> x(2);
	ft::vector<int> iter(*list, *list + 3);

	iter[0] = 'A';
	std::cout << iter[0] << std::endl;
	def.assign(10, 20);
	copy.assign(def.begin(), def.end());
	return 0;
}
