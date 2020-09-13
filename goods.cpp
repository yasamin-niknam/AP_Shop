#include"goods.hpp"

using namespace std;

Goods:: Goods(vector<string> command)
{
	owners_username = command[1];
	goods_name = command[2];
	goods_price = stoi(command[3]);
	goods_count = stoi(command[4]);
}

void Goods::add_count(int num)
{
	goods_count += num;
}

bool Goods::is_needed_goods(string _goods_name, int num_of_needed)
{
	return	(is_same_goods(_goods_name) && (get_count() >= num_of_needed));
}

void Goods::print()
{
	cout << goods_name << " " << goods_count << " " << goods_price << " " << owners_username << endl;
}

void Goods::print_goods()
{
	cout << goods_name << " " << goods_count << " " << goods_price
	 << " " << owners_username << endl;
}

bool Goods::does_not_have_this_suggestion(string name)
{
	for (int i = 0; i < suggested_sale_usernames.size(); i++)
	{
		if( name == suggested_sale_usernames[i])
			return false;
	}
	return true;
}