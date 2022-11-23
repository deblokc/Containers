/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_rbt.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:49:18 by tnaton            #+#    #+#             */
/*   Updated: 2022/11/23 20:55:47 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbt.hpp"
#include <iostream>
#include <map>
#include "map.hpp"

struct Trunk
{
    Trunk *prev;
	std::string str;
 
    Trunk(Trunk *prev, std::string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

void showTrunks(Trunk *p)
{
    if (p == NULL) {
        return;
    }

    showTrunks(p->prev);
	std::cout << p->str;
}

void printnode(ft::rbt<int, int>::node & tmp) {
	if (!tmp) {
		std::cout << "Invalide insert" << std::endl;
		return ;
	}
	if (tmp->color)
		std::cout << "\033[0;90m"; 
	else
		std::cout << "\033[0;91m";
	std::cout << "Key : " << tmp->val.first << " | Val : " << tmp->val.second << "\033[0m" << std::endl;
}

void printTree(ft::rbt<int, int>::node root, Trunk *prev, bool isLeft) {
	if (root == NULL)
		return ;
	std::string prev_str = "         ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->r, trunk, true);

    if (!prev) {
        trunk->str = "—————————";
    }
    else if (isLeft)
    {
        trunk->str = ".—————————";
        prev_str = "         |";
    }
    else {
        trunk->str = "`—————————";
        prev->str = prev_str;
    }

    showTrunks(trunk);
	if (root->color)
		std::cout << "\033[0;90m"; 
	else
		std::cout << "\033[0;91m";
	std::cout << " " << root->val.first << "\033[0m" << std::endl;

    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "         |";

    printTree(root->l, trunk, false);
	delete trunk;
}

void pT(ft::rbt<int, int>::node root) {
	printTree(root, NULL, false);
	std::cout << "-------------------------------------------------------------------------------------" << std::endl;
}

int main(void) {

//	typedef ft::map<int, int>::const_iterator	const_iterator;

	ft::map<int, int>	test;
//	ft::map<int, int>	map2;

	test.insert(ft::pair<int, int>(23, 1));
	pT(test.root());
	test.insert(ft::pair<int, int>(25, 1));
	pT(test.root());
	test.insert(ft::pair<int, int>(1, 1));
	pT(test.root());
	test.insert(ft::pair<int, int>(2, 1));
	pT(test.root());
	test.insert(ft::pair<int, int>(3, 1));
	pT(test.root());
	test.insert(ft::pair<int, int>(75, 1));
	pT(test.root());
	test.insert(ft::pair<int, int>(30, 1));
	pT(test.root());
	test.insert(ft::pair<int, int>(-22, 1));
	pT(test.root());
	test.insert(ft::pair<int, int>(-23, 1));
	pT(test.root());

	
	std::cout << "####################################################################################" << std::endl;

	ft::rbt<int, int>::node x = test.root();

	typedef ft::map<int, int>::iterator			iterator;

	iterator it = test.begin();

	it++;
	it++;
	it++;
	it++;

	ft::rbt<int, int>::node y = it.base();

	pT(test.root());

	std::cout << "trying to swap " << x->val.first << " and " << y->val.first << std::endl;
	std::cout << "-------------------------------------------------------------------------------------" << std::endl;

	pT(test.root());
/*
	typedef ft::map<int, int>::iterator			iterator;
	for (iterator it = test.begin(); it != test.end(); it++)
		std::cout << it->first << "|" << it->second << std::endl;
	test.size();

	std::cout << "####################################################################################" << std::endl;

	test.insert(ft::pair<int, int>(0, 1));
	pT(test.root());
	
	std::cout << "####################################################################################" << std::endl;

	for (iterator it = test.begin(); it != test.end(); it++)
		std::cout << it->first << "|" << it->second << std::endl;
	test.size();

	std::cout << "####################################################################################" << std::endl;

	pT(test.root());
	test.erase(2);
	pT(test.root());
	test.erase(75);
	pT(test.root());
	test.erase(1);
	pT(test.root());
	test.erase(23);
	pT(test.root());
	test.erase(3);
	pT(test.root());
	test.erase(30);
	pT(test.root());
	test.erase(-22);
	pT(test.root());
	test.erase(-23);
	pT(test.root());
	test.erase(25);
	pT(test.root());
	test.erase(75);
	pT(test.root());
*/
//	typedef ft::map<int, int>::iterator iterator;
	


//	map2 = test;

//	iterator it = test.begin();
//	std::cout << it->first << "|" << it->second << std::endl;
//	it->second = 10;

//	const_iterator cit = test.begin();
//	std::cout <<cit->first << "|" <<cit->second << std::endl;

//	iterator t = test.end();
//	t--;

/*	typedef ft::map<int, int>::reverse_iterator		reverse_iterator;

	for (reverse_iterator rit = test.rbegin(); rit != test.rend(); rit++) {
		std::cout << rit->first << "|" << rit->second << std::endl;
	}
*/


/*	ft::rbt<int, int>		test;
	std::map<int, int>		std;

	test.insert(ft::pair<int, int>(3, 1));
	std.insert(std::pair<int, int>(3, 1));

	test.insert(ft::pair<int, int>(0, 1));
	std.insert(std::pair<int, int>(0, 1));

	test.insert(ft::pair<int, int>(9, 5));
	std.insert(std::pair<int, int>(9, 5));

	test.insert(ft::pair<int, int>(10, 2));
	std.insert(std::pair<int, int>(10, 2));

	ft::pair<ft::rbt<int,int>::iterator,bool> jsp = test.insert(ft::pair<int, int>(42, 42));
	test.insert(ft::pair<int, int>(4, 4));
	test.insert(ft::pair<int, int>(2, 2));
	test.insert(ft::pair<int, int>(23, 5));
	test.insert(ft::pair<int, int>(4, 2));
	test.insert(ft::pair<int, int>(2, 4));
	test.insert(ft::pair<int, int>(69, 102));
	test.insert(ft::pair<int, int>(52, 2));
	test.insert(ft::pair<int, int>(22, 0));
	test.insert(ft::pair<int, int>(12, 2));
	test.insert(ft::pair<int, int>(4, 32));
	test.insert(ft::pair<int, int>(53, 53));
	test.insert(ft::pair<int, int>(70, 53));

	std.insert(std::pair<int, int>(42, 42));
	std.insert(std::pair<int, int>(4, 4));
	std.insert(std::pair<int, int>(2, 2));
	std.insert(std::pair<int, int>(23, 5));
	std.insert(std::pair<int, int>(4, 2));
	std.insert(std::pair<int, int>(2, 4));
	std.insert(std::pair<int, int>(69, 102));
	std.insert(std::pair<int, int>(52, 2));
	std.insert(std::pair<int, int>(22, 0));
	std.insert(std::pair<int, int>(12, 2));
	std.insert(std::pair<int, int>(4, 32));
	std.insert(std::pair<int, int>(53, 53));
	std.insert(std::pair<int, int>(70, 53));

	printTree(test.root(), NULL, false);

	for (std::map<int, int>::iterator tmp = std.begin(); tmp != std.end(); tmp++) {
		std::cout << tmp->first << "|" << tmp->second << std::endl;
	}

	std::cout << std::endl;

	ft::rbt<int, int>::iterator it = test.begin();

	std::cout << it->first << "|" << it->second << std::endl;
	it++;
	std::cout << it->first << "|" << it->second << std::endl;
	it++;
	std::cout << it->first << "|" << it->second << std::endl;
	it++;
	std::cout << it->first << "|" << it->second << std::endl;

	std::cout << std::endl;

	for (ft::rbt<int, int>::iterator tmp = test.begin(); tmp != test.end(); tmp++) {
		std::cout << tmp->first << "|" << tmp->second << std::endl;
	}
	std::cout << std::endl << "ERASE" << std::endl << std::endl;
*/
/*
 * Obvious invalid read

	for (std::map<int, int>::iterator tmp = std.begin(); tmp != std.end(); tmp++) {
		std::cout << tmp->first << "|" << tmp->second << std::endl;
		std.erase(tmp);
	}
*/

//	std::cout << "FT" << std::endl;
//	ft::rbt<int, int>::iterator tmp = test.find(42);
//	std::cout << tmp->first << "|" << tmp->second << std::endl;
//	test.erase(jsp.first);
//	printTree(test.root(), NULL, false);
//	std::cout << "FT" << std::endl;
/*
	while (test.begin() != test.end()) {
		test.erase(test.begin());
		std::cout << std::endl;
		printTree(test.root(), NULL, false);
		std::cout << std::endl;
	}
*/
}
