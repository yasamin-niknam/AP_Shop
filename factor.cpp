#include "factor.hpp"

using namespace std;

Factor::Factor(string _buyer_username, string _goods_name, int _goods_count , string _seller_username)
{
	buyer_username = _buyer_username;
	goods_name.push_back(_goods_name);
	goods_count.push_back(_goods_count);
	price.push_back(0);
	sum.push_back(0);
	seller_username.push_back(_seller_username);
}

void Factor::add_goods(std::string _goods_name, int _goods_count , std::string _seller_username)
{
	goods_name.push_back(_goods_name);
	goods_count.push_back(_goods_count);
	price.push_back(0);
	sum.push_back(0);
	seller_username.push_back(_seller_username);
}

bool Factor::buy(vector<Person*> users, int& money_added_to_shoppingcenter)
{
	int index_of_seller = -1;
	int index_of_buyer = -1;
	for (int i = 0; i < goods_count.size(); i++)
	{
		for (int j = 0; j < users.size(); j++)
		{
			if(users[j]->is_the_same_username(buyer_username) && users[j]->is_buyer)
				index_of_buyer = j;
			if(users[j]->is_the_same_username(seller_username[i]) && users[j]->is_seller)
				index_of_seller = j;
		}
	}
	bool seller_and_buyer_existed = (index_of_buyer != -1) && (index_of_seller != -1);
	if(seller_and_buyer_existed == false)
		return false;
	for (int i = 0; i < goods_count.size() ; i++)
	{
		if(users[index_of_seller]->seller->has_enough_goods(goods_name[i], goods_count[i]) == false)
			return false;
	}
	int money_needed = calc_money_needed(users);
	if(money_needed == 0)
		return false;
	if(money_needed <= users[index_of_buyer]->get_money())
	{
		users[index_of_seller]->add_money(money_needed);
		users[index_of_buyer]->add_money((-1.05)* money_needed);
		money_added_to_shoppingcenter = 0.05 * money_needed;
		return true;
	}
	else 
		return false;	
}

void Factor::decrease_num_of_goods(vector<Person*> users)
{
	int index_of_seller ;
	for (int i = 0; i < goods_count.size(); i++)
	{
		for (int j = 0; j < users.size(); j++)
		{
			if(users[j]->is_the_same_username(seller_username[i]) && users[j]->is_seller)
			{
				index_of_seller = j;
				users[index_of_seller]->seller->decrease_num_of_goods(goods_name[i], goods_count[i]);
				break;
			}
		}
	}
}

int Factor::calc_money_needed(vector<Person*> users)
{
	Goods* goods = NULL;
	int money_needed = 0;
	for (int i = 0; i < goods_count.size(); i++)
	{
		for (int j = 0; j < users.size(); j++)
		{
			if(users[j]->is_the_same_username(seller_username[i]) && users[j]->is_seller)
			{
				goods = users[j]->seller->find_needed_goods(goods_name[i], goods_count[i]);
				break;
			}
		}
		if(goods != NULL)
		{
			if(goods->is_on_sale() || goods->has_special_price())
				money_needed += (goods_count[i] * 0.9 * goods->get_price());
			else
				money_needed += (goods_count[i] * goods->get_price());
		}
		else
			continue;
	}
	return money_needed;
}

void Factor::print_factor(vector<Person*> users)
{
	Goods* goods = NULL;
	int _price = 0;
	int goods_sum = 0;
	int money_needed = 0;
	bool information_printed = false;
	for (int i = 0; i < goods_count.size(); i++)
	{
		for (int j = 0; j < users.size(); j++)
		{
			if(users[j]->is_the_same_username(buyer_username) && !information_printed)
			{
				information_printed = true;
				users[j]->print_information();
				continue;
			}
			if(users[j]->is_the_same_username(seller_username[i]) && users[j]->is_seller)
			{
				goods = users[j]->seller->find_needed_goods(goods_name[i], goods_count[i]);
			}
		}
			if(goods != NULL)
			{
				if(goods->is_on_sale() || goods->has_special_price())
					_price = 0.9 * goods->get_price();
				else
					_price = goods->get_price();
			}
			else
				continue;
	}
	for (int i = 0; i < goods_name.size(); i++)
	{
		money_needed = calc_money_needed(users);
		if(sum[i] == 0)
			sum[i] = money_needed;
		if(price[i] == 0)		
			price[i] = _price;
		goods_sum += sum[i];
		cout << i+1 << ". " << goods_name[i] << " | " << goods_count[i] << " | " << price[i] 
				<< " | " << seller_username[i] << " | " << sum[i] << endl;
	}
	cout << "Goods Sum = " << goods_sum << endl;
	cout << "Total Sum = " << (goods_sum * 1.05 ) << endl;
}

void Factor::change_request_to_factor(Request* request)
{
	string _buyer_username = request->get_buyer_username();
	buyer_username = _buyer_username;
	vector<string> _seller_username = request->get_seller_usernames();
	for (int i = 0; i < _seller_username.size(); i++)
		seller_username.push_back(_seller_username[i]);
	vector<string> _goods_name = request->get_goods_name();
	for (int i = 0; i < _goods_name.size(); i++)
		goods_name.push_back(_goods_name[i]);
	vector<int> _goods_count = request->get_goods_count();
	for (int i = 0; i < _goods_count.size(); i++)
	{
		goods_count.push_back(_goods_count[i]);
		sum.push_back(0);
		price.push_back(0);
	}
}

bool Factor::check_if_goods_existed(vector<Person*> users)
{
	for (int i = 0; i < goods_name.size(); i++)
	{
		for (int j = 0; j < users.size(); j++)
		{
			if(users[j]->seller != NULL && users[j]->is_the_same_username(seller_username[i]))
			{
				if(users[j]->seller->check_if_goods_exist(goods_name[i], goods_count[i]) == false)
					return false;
			}
		}
	}
	return true;
}
