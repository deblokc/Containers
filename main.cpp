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
#include <string>
#include <vector>

int main () {

    {
		ft::vector<char> v;

        v.assign(0, 'c');
        v.assign(64, 'A');
        v.assign(32, '5');
        v.assign(49, '8');
        v.assign(77, '2');
    }

    {
		ft::vector<std::string> v;

        v.assign(0, "");
        v.assign(64, "vector-string");
    }
}
