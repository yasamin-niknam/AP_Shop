#ifndef SELLER
#define SELLER

#include <iostream>
#include <vector>
#include "goods.hpp" 



class Seller
{
public:
	Seller() {}
	void add_goods(Goods* _goods);
	Goods* find_needed_goods(std::string _goods_name, int num_of_needed);
	bool add_sale_suggestion(std::string _goods_name, std::string _username);
	bool add_special(std::string _goods_name);
	bool remove_special(std::string _goods_name);
	int get_num_of_goods(){return all_goods.size();}
	bool check_if_goods_exist(std::string goods_name, int goods_count);
	void decrease_num_of_goods(std::string goods_name, int goods_count);
	void check_sale_suggestions();
	bool has_enough_goods(std::string goods_name, int _goods_count);
	std::vector<Goods*> search_sale();
	std::vector<Goods*> search_bestsellers();
private:
	std::vector<Goods*> all_goods;	
};




#endif