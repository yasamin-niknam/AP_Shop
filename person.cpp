#include "person.hpp"

using namespace std;

Person:: Person(vector<string> command)
{
	first_name = command[1];
	last_name = command[2];
	username = command[3];
	phone_number = command[4];
	money = stoi(command[5]);
	if(command[6] == "seller")
	{
		seller = new Seller();
		is_seller = true;
	}
	else if(command[6] == "buyer")
		is_buyer = true;
}

void Person::print_information()
{
	cout << first_name << " " << last_name << " " << username << " " << phone_number  << endl;
}

bool Person::is_the_same_person(vector<string> command)
{
	return (first_name == command[1] && last_name == command[2] && username == command[3] && phone_number == command[4]);
}

vector<Goods*> Person::find_goods(string _goods_name, int num_of_needed)
{
	vector<Goods*> founded_goods;
	if(is_seller && (seller->find_needed_goods(_goods_name, num_of_needed) != NULL))
	{
		founded_goods.push_back(seller->find_needed_goods(_goods_name, num_of_needed)) ;		
	}
	return founded_goods;
}
