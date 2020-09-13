#ifndef FACTOR
#define FACTOR

#include <iostream>
#include <vector>
#include "person.hpp"
#include "goods.hpp"
#include "seller.hpp"
#include "request.hpp"

class Factor
{
public:
	Factor(std::string _buyer_username, std::string _goods_name, int _goods_count , std::string _seller_username);
	Factor() {}
	void add_goods(std::string _goods_name, int _goods_count , std::string _seller_username);
	bool buy(std::vector<Person*> users, int& money_added_to_shoppingcenter);
	int calc_money_needed(std::vector<Person*> users);	
	bool is_same_buyer(std::string _buyer_username){return (buyer_username == _buyer_username);}
	void print_factor(std::vector<Person*> users);
	void change_request_to_factor(Request* request);
	bool check_if_goods_existed(std::vector<Person*> users);
	void decrease_num_of_goods(std::vector<Person*> users);
private:
	std::string buyer_username;
	std::vector<std::string> goods_name;
	std::vector<int> goods_count;
	std::vector<int> sum;
	std::vector<int> price;
	std::vector<std::string> seller_username;	
};



#endif