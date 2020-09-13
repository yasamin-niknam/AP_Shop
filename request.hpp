#ifndef REQUEST
#define REQUEST

#include <iostream>
#include <vector>

class Request
{
public:
	Request(std::vector<std::string> splitted_command);
	void print();
	void add_goods(std::string goods_name, int goods_count, std::string seller_username);
	bool is_same_buyer(std::string _buyer_username){return (buyer_username == _buyer_username);}
	std::string get_buyer_username(){return buyer_username;}
	std::vector<std::string> get_seller_usernames(){return seller_username;}
	std::vector<std::string> get_goods_name(){return goods_name;}
	std::vector<int> get_goods_count(){return goods_count;}
private:
	std::string request_name;
	std::string buyer_username;
	std::vector<std::string> seller_username;
	std::vector<std::string> goods_name;
	std::vector<int> goods_count;	
};

#endif