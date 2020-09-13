#ifndef PERSON
#define PERSON

#include <iostream>
#include <vector>
#include "seller.hpp"

class Person
{
public:
	Person(std::vector<std::string> command);
	bool is_the_same_username(std::string _username){return username == _username;}
	bool is_the_same_person(std::vector<std::string> command);
	std::vector<Goods*> find_goods(std::string _goods_name, int num_of_needed);
	void add_money(int added_money){money += added_money;}
	int get_money(){return money;}
	std::string show(){return username;}
	void print_information();
	bool is_seller = false;
	bool is_buyer = false;
	Seller* seller = NULL;
private:
	int money;
	std::string username;
	std::string first_name;
	std::string last_name;
	std::string phone_number;
};



#endif