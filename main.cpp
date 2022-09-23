/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:09:37 by tnaton            #+#    #+#             */
/*   Updated: 2022/09/23 16:45:08 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "iterator.hpp"
#include "iterator_traits.hpp"
#include "stack.hpp"
#include "vector.hpp"

int main () {
	int list[] = {0, 1, 2, 3};
	ft::vector<int> def;
	ft::vector<int> copy(def);
	ft::vector<char> xval(10, 'c');
	ft::vector<int> x(2);
	ft::vector<int> iter(*list, *list + 3);

	return 0;
}
