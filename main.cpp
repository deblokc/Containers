/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:09:37 by tnaton            #+#    #+#             */
/*   Updated: 2022/09/23 12:16:46 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "iterator.hpp"
#include "iterator_traits.hpp"
#include "stack.hpp"
#include "vector.hpp"

int main () {
	ft::vector<int> test;
	ft::vector<int> retest(test);
	return 0;
}