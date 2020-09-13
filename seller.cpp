#include "seller.hpp"

using namespace std;


void Seller::add_goods(Goods* _goods)
{
	bool necessary_to_add = true;
	for (int i = 0; i < all_goods.size(); i++)
	{
		if(all_goods[i]->is_same_goods(_goods->get_goods_name()))
		{
			all_goods[i]->add_count(_goods->get_count());
			necessary_to_add = false;
			break;
		}	
	}
	if(necessary_to_add)
		all_goods.push_back(_goods);
}

Goods* Seller::find_needed_goods(string _goods_name, int num_of_needed)
{
	for (int i = 0; i < all_goods.size(); i++)
	{
		if(all_goods[i]->is_needed_goods(_goods_name, num_of_needed))
		{
			return all_goods[i];
		}
	}
	Goods* goods = NULL ;
	return goods;
}

bool Seller::add_sale_suggestion(string _goods_name, string _username)
{
	for (int i = 0; i < all_goods.size(); i++)
	{
		if(all_goods[i]->is_same_goods(_goods_name) && all_goods[i]->does_not_have_this_suggestion(_username))
		{
			all_goods[i]->add_sale_suggestion(_username);
			return true;
		}
	}
	return false;
}

bool Seller::add_special(string _goods_name)
{
	for (int i = 0; i < all_goods.size(); i++)
	{
		if(all_goods[i]->is_same_goods(_goods_name))
		{
			all_goods[i]->add_special();
			return true;
		}
	}
	return false;
}

bool Seller::remove_special(string _goods_name)
{
	for (int i = 0; i < all_goods.size(); i++)
	{
		if(all_goods[i]->is_same_goods(_goods_name))
		{
			all_goods[i]->remove_special();
			return true;
		}
	}
	return false;
}

vector<Goods*> Seller::search_sale()
{
	vector<Goods*> on_sale_goods;	
	for (int i = 0; i < all_goods.size(); i++)
	{
		if(all_goods[i]->has_special_price() || all_goods[i]->is_on_sale() || all_goods[i]->is_on_sale_from_shoppingcenter())
			on_sale_goods.push_back(all_goods[i]);
	}
	return on_sale_goods;
}

void Seller::check_sale_suggestions()
{
	for (int i = 0; i < all_goods.size(); i++)
	{
		if(all_goods[i]->get_num_of_suggestions() > 10)
			all_goods[i]->start_sale();
	}
}

bool Seller::check_if_goods_exist(std::string goods_name, int goods_count)
{
	for (int i = 0; i < all_goods.size(); i++)
	{
		if(all_goods[i]->is_the_same_goods(goods_name, goods_count))
			continue;
		else
			return false;
	}
	return true;
}

void Seller::decrease_num_of_goods(string goods_name, int goods_count)
{
	for (int i = 0; i < all_goods.size(); i++)
	{
		if(all_goods[i]->is_same_goods(goods_name))
		{
			all_goods[i]->decrease_num_of_goods(goods_count);
			all_goods[i]->increase_num_of_soled();
			break;
		}
	}
}

bool Seller::has_enough_goods(string goods_name, int _goods_count)
{
	for (int i = 0; i < all_goods.size(); i++)
	{
		if(all_goods[i]->is_same_goods(goods_name))
		{
			if(all_goods[i]->has_enough_count(_goods_count))
				return true;
			else
				return false;
		}
	}
}

vector<Goods*> Seller::search_bestsellers()
{
	vector<Goods*> bestsellers;
 	for (int i = 0; i < all_goods.size(); i++)
	{
		if(all_goods[i]->get_num_of_soled() > 10)
			bestsellers.push_back(all_goods[i]);
	}
	return bestsellers;
}
