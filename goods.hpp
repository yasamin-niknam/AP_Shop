#ifndef GOODS
#define GOODS

#include <iostream>
#include <vector>

class Goods
{
public:
	Goods(std::vector<std::string> command);
	void print();
	void print_goods();
	bool is_on_sale(){return on_sale;}
	bool is_on_sale_from_shoppingcenter(){return sale_is_from_shoppingcenter;}
	bool has_special_price(){return special_price;}
	bool does_not_have_this_suggestion(std::string name);
	bool is_the_same_goods(std::string _goods_name, int _goods_count)
		{return ((_goods_name == goods_name) && (_goods_count == goods_count));}
	int get_count(){return goods_count;}
	int get_price(){return goods_price;}
	int get_num_of_suggestions(){return suggested_sale_usernames.size();}
	bool is_same_goods(std::string name) {return name == goods_name;}
	bool is_needed_goods(std::string _goods_name, int num_of_needed);
	bool has_enough_count(int _goods_count) {return (goods_count >= _goods_count);}
	void add_count(int num);
	void add_sale_suggestion(std::string _username){suggested_sale_usernames.push_back(_username);}
	void add_special(){special_price = true;}
	void remove_special(){special_price = false;}
	void start_sale(){on_sale = true;}
	void end_sale(){on_sale = false;}
	void start_sale_from_shoppingcenter(){sale_is_from_shoppingcenter = true;}
	void end_sale_from_shoppingcenter(){sale_is_from_shoppingcenter = false;}
	void decrease_num_of_goods(int _goods_count){goods_count -= _goods_count;}
	void increase_num_of_soled(){num_of_soled++;}
	int get_num_of_soled(){return num_of_soled;}
	std::string get_goods_name() {return goods_name;}
	std::string get_seller_username() {return owners_username;}

private:
	int goods_price;
	int goods_count;
	bool special_price = false;
	bool on_sale = false;
	int num_of_soled = 0;
	bool sale_is_from_shoppingcenter = false;
	std::string goods_name;
	std::string owners_username;
	std::vector<std::string> suggested_sale_usernames;
};





#endif