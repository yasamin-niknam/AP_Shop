#include "request.hpp"

using namespace std;

Request::Request(vector<string> splitted_command)
{
	request_name = splitted_command[1];
	buyer_username= splitted_command[2];
	goods_name.push_back(splitted_command[3]);
	goods_count.push_back(stoi(splitted_command[4]));
	seller_username.push_back(splitted_command[5]);
}

void Request::add_goods(string _goods_name, int _goods_count, string _seller_username)
{
	goods_name.push_back(_goods_name);
	goods_count.push_back(_goods_count);
	seller_username.push_back(_seller_username);
}

void Request::print()
{
	cout << request_name << " " << buyer_username << endl; 
	for (int i = 0; i < goods_name.size(); i++)
		cout << (i + 1) << ". " << goods_name[i] << " " << goods_count[i] << " " << seller_username[i] << endl ;
}
