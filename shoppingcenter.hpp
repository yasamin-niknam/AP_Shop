#ifndef SHOPPINGCENTER
#define SHOPPINGCENTER

#include <iostream>
#include <vector>
#include "goods.hpp"
#include "seller.hpp"
#include "factor.hpp"
#include "person.hpp"
#include "request.hpp"

#define NOT_FOUND -1
#define OK_MSG "Command OK"
#define FAILED_MSG "Command Failed"
#define ALPHABETIC "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ@._-0123456789,;"

class ShoppingCenter
{
public:
	ShoppingCenter() {}
	void process(std::string command);
private:
	int money = 0;
	std::vector<Person*> users;
	std::vector<Factor*> factors;
	std::vector<Request*> requests;
	std::vector<std::string> split_command(std::string command);
	void add_user(std::vector<std::string> splitted_command);
	void add_goods(std::vector<std::string> splitted_command);
	void search_goods(std::vector<std::string> splitted_command);
	void sale(std::vector<std::string> splitted_command);
	void add_special(std::vector<std::string> splitted_command);
	void remove_special(std::vector<std::string> splitted_command);
	void add_money(std::vector<std::string> splitted_command);
	void buy(std::vector<std::string> splitted_command);
	void request(std::vector<std::string> splitted_command);
	void print_request(std::string buyer_username);
	void print_factor(std::string buyer_username);
	void check_for_sale();
	void search_sale();
	void check_requests();
	void swap_goods(Goods*& goods1, Goods*& goods2);
	void sort_on_sale_goods(std::vector<Goods*> all_goods);
	bool search_goods_sort(std::vector<Goods*>& all_goods);
	void search_bestseller();
};

#endif