/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_rbt.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:49:18 by tnaton            #+#    #+#             */
/*   Updated: 2022/12/09 20:25:03 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbt.hpp"
#include <iostream>
#include <map>
#include "map.hpp"
#include "set.hpp"
#include "vector.hpp"

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

void printnode(ft::rbt<int, int, ft::pair<const int, int>, ft::map<int, int>::value_compare>::node & tmp) {
	if (!tmp) {
		std::cout << "Invalide insert" << std::endl;
		return ;
	}
	if (tmp->color)
		std::cout << "\033[0;90m"; 
	else
		std::cout << "\033[0;91m";
	std::cout << "Key : " << tmp->val << " | Val : " << tmp->val << "\033[0m" << std::endl;
}

void printTree(ft::rbt<int, int, ft::pair<const int, int>, ft::map<int, int>::value_compare >::node root, Trunk *prev, bool isLeft) {
	if (root == NULL || root->val == NULL)
		return ;
	std::string prev_str = "         ";
    Trunk *trunk = new Trunk(prev, prev_str);

//	std::cout << root->val->first << std::endl;

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
	std::cout << " " << root->val->first << "\033[0m" << std::endl;

    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "         |";

    printTree(root->l, trunk, false);
	delete trunk;
}

void pT(ft::rbt<int, int, ft::pair<const int, int>, ft::map<int, int>::value_compare >::node root) {
	printTree(root, NULL, false);
	std::cout << "-------------------------------------------------------------------------------------" << std::endl;
}

/*
void printMap(const ft::map<int, int> & m) {
	std::cout << "PRINT WITH CONST_ITERATOR" << std::endl;
	for (ft::map<int, int>::const_iterator it = m.begin(); it != m.end(); it++) {
		std::cout << it->second << std::endl;
	}
	std::cout << "PRINT WITH CONST_REVERSE_ITERATOR" << std::endl;
	for (ft::map<int, int>::const_reverse_iterator rit = m.rbegin(); rit != m.rend(); rit++) {
		std::cout << rit->second << std::endl;
	}
}
*/


#include "42ft_containers_tester/vector/includes/ConstClass.hpp"
int main(void) {


	for (volatile int i = 0; i < 1; i++)
	{
		ft::vector<ConstClass>			test;
		ft::vector<ConstClass>::iterator	it;

		test.reserve(50);
		it = test.begin();
		test.insert(test.end(), 4, ConstClass(420));
		test.insert((test.begin() + 1), 13, ConstClass(666));
		for (; it != test.end(); it++)
		{
			std::cout << *it << "|" << it.base() << std::endl;
		}
		test.insert((test.begin()), 50, ConstClass(888));
		for (it = test.begin(); it != test.end(); it++)
		{
			std::cout << *it << std::endl;
		}
	}

/*

	ConstClass	tab[] = {ConstClass(), ConstClass(2), ConstClass(10)};
	ConstClass	tab2[] = {ConstClass(666), ConstClass(42)};
	for (volatile int i = 0; i < 1; i++)
	{
		ft::vector<ConstClass>	test;


		test.reserve(50);
		test.insert(test.begin(), tab, tab+3);
		test.insert(test.begin(), tab2, tab2+2);
		test.insert(test.end(), tab2, tab2+1);
		std::cout << "*******************************************************************" << std::endl;
		std::cout << "BEFORE INSERT : " << std::endl;
		for (ft::vector<ConstClass>::iterator it = test.begin(); it != test.end(); it++)
		{
			std::cout << *it << "|" << it.base() << std::endl;
		}
		std::cout << "*******************************************************************" << std::endl;
		std::cout << "TRYING TO INSERT :" << std::endl;

		std::cout << *tab2 << std::endl;
		std::cout << *(tab2+1) << std::endl;

		std::cout << "*******************************************************************" << std::endl;
		test.insert((test.begin() + 5), tab2, tab2+2);
		for (ft::vector<ConstClass>::iterator it = test.begin(); it != test.end(); it++)
		{
			std::cout << *it << "|" << it.base() << std::endl;
		}
		std::cout << "Capacity: " << test.capacity() << std::endl;
	}
*/
	/*
	ft::map<int, int> m;

	m[0] = 0;
//	pT(m.root());
	m[1] = 0;
//	pT(m.root());
	m[2] = 0;
//	pT(m.root());
	m[3] = 0;
//	pT(m.root());
	m[4] = 0;
//	pT(m.root());
	m[5] = 0;
//	pT(m.root());
	m[6] = 0;
//	pT(m.root());
	m[7] = 0;
//	pT(m.root());
	m[8] = 0;
//	pT(m.root());
	m[9] = 0;
//	pT(m.root());*/
/*
	std::cout << "=========PRINT IN (END--)========" << std::endl;
	ft::map<int, int>::iterator it = m.end();
	it--;
	std::cout << it->first << std::endl;
	std::cout << "=========PRINT IN ORDER========" << std::endl;
	for (ft::map<int, int>::iterator it = m.begin(); it != m.end(); it++) {
		std::cout << it->first << std::endl;
	}
	std::cout << "=========PRINT IN REVERSE ORDER========" << std::endl;
	for (ft::map<int, int>::reverse_iterator it = m.rbegin(); it != m.rend(); it++) {
		std::cout << it->first << std::endl;
	}
*/
//	ft::map<int, int> test;

//	test = m;
/*
	std::cout << "base tree" << std::endl;
	pT(m.root());
	std::cout << "test tree" << std::endl;
	pT(test.root());
*//*
	for (ft::map<int, int>::iterator it = m.begin(); it != m.end(); it++) {
		std::cout << it->first << std::endl;
	}

	for (ft::map<int, int>::iterator it = test.begin(); it != test.end(); it++) {
		std::cout << it->first << std::endl;
	}
*/


/*
	using namespace ft;

  map<char,int> foo,bar;

  foo['x']=100;
  foo['y']=200;

  bar['a']=11;
  bar['b']=22;
  bar['c']=33;


  map<char, int>::const_iterator tmp = foo.begin(); //tmp iterates through foo
  map<char, int>::const_iterator tmp2 = bar.begin(); //tmp2 iterates through bar

  swap(bar, foo); //tmp iterates through bar
				//tmp2 iterates through foo


  map<char, int>	other;

  other['1'] = 73;
  other['2'] = 173;
  other['3'] = 763;
  other['4'] = 73854;
  other['5'] = 74683;
  other['6'] = 753;

  map<char, int>::const_iterator tmp3 = other.begin(); // tmp3 iterates through other

 std::cout << "foo contains:\n";
  for (map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
   std::cout << it->first << " => " << it->second << '\n';

 std::cout << "bar contains:\n";
  for (map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
   std::cout << it->first << " => " << it->second << '\n';

	while(tmp != bar.end())
	{
	std::cout << tmp->first << " => " << tmp->second << '\n';
		tmp++;
	}
	tmp--;

	while(tmp2 != foo.end())
	{
	std::cout << tmp2->first << " => " << tmp2->second << '\n';
		tmp2++;
	}
	tmp2--;

	swap(other, foo); //tmp2 iterates through other
					//tmp3 iterates throught foo
	pT(other.root());
	pT(foo.root());
	pT(bar.root());
	while(tmp != bar.begin())
	{
	std::cout << tmp->first << " => " << tmp->second << '\n';
		tmp--;
	}
std::cout << tmp->first << " => " << tmp->second << '\n';

	while(tmp2 != other.begin())
	{
	std::cout << tmp2->first << " => " << tmp2->second << '\n';
		tmp2--;
	}
std::cout << tmp2->first << " => " << tmp2->second << '\n';

	while(tmp3 != foo.end())
	{
	std::cout << tmp3->first << " => " << tmp3->second << '\n';
		tmp3++;
	}
	tmp3--;

	swap(bar, foo);
	swap(foo, bar);
	swap(bar, foo); //tmp3 iterates through bar
				//tmp iterates through foo

	pT(other.root());
	pT(foo.root());
	pT(bar.root());

	while(tmp != foo.end())
	{
	std::cout << tmp->first << " => " << tmp->second << '\n';
		tmp++;
	}

	while(tmp2 != other.end())
	{
	std::cout << tmp2->first << " => " << tmp2->second << '\n';
		tmp2++;
	}

	while(tmp3 != bar.begin())
	{
	std::cout << tmp3->first << " => " << tmp3->second << '\n';
		tmp3--;
	}
std::cout << tmp3->first << " => " << tmp3->second << '\n';
*/
/*

	typedef ft::map<int, int>::iterator iterator;
	typedef ft::map<int, int>::reverse_iterator riterator;

	ft::map<int, int> m;

	m[0] = 42;
	m[1] = 42;
	m[2] = 42;

	for (iterator it = m.begin(); it != m.end(); it++) {
		std::cout << it->first << std::endl;
	}

	for (riterator it = m.rbegin(); it != m.rend(); it++) {
		std::cout << it->first << std::endl;
	}

	ft::map<int,int> test(m);

	test = m;
	m = test;*/
	/*
	ft::vector<int> v(20, 2);
	ft::vector<int> data(4, 42);
	std::cout << std::endl;
	v.insert(v.begin() + 4, data.begin(), data.begin() + 2);
	for (ft::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		std::cout << *it << std::endl;
	}*/
//	ft::map<int, int>	test;
//	ft::map<int, int>	map2;
/*
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

	typedef ft::map<int, int>::iterator			iterator;
	for (iterator it = test.begin(); it != test.end(); it++)
		std::cout << it->first << "|" << it->second << std::endl;
	
	std::cout << "####################################################################################" << std::endl;

	ft::rbt<int, int>::node y = test.find(3).base();
	ft::rbt<int, int>::node x = test.find(2).base();

	pT(test.root());

	std::cout << "trying to swap " << x->val.first << " and " << y->val.first << std::endl;
	std::cout << "-------------------------------------------------------------------------------------" << std::endl;

//	x->swap(y);

	pT(test.root());

	std::cout << "-22's parent is " << test.find(-22).base()->parent->val.first << std::endl;
	std::cout << "-22's brother is " << test.find(-22).base()->parent->r->val.first << std::endl;

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

	for (iterator it = test.begin(); it != test.end(); it++)
		std::cout << it->first << "|" << it->second << std::endl;

	std::cout << "$$$$$$$$$" << std::endl;

	test.debug();

	std::cout << "$$$$$$$$$" << std::endl;

	pT(test.root());
	while (test.size()) {
		test.erase(test.root()->val.first);
		pT(test.root());
    }

	ft::set<int> set;
	set.insert(1);
//	typedef ft::map<int, int>::iterator iterator;
	


//	map2 = test;

//	iterator it = test.begin();
//	std::cout << it->first << "|" << it->second << std::endl;
//	it->second = 10;

//	const_iterator cit = test.begin();
//	std::cout <<cit->first << "|" <<cit->second << std::endl;

//	iterator t = test.end();
//	t--;
*/
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
