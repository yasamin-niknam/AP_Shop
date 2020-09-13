#include "shoppingcenter.hpp"

using namespace std;

vector<string> ShoppingCenter::split_command(string command)
{
  vector<string> splitted_command;
  string word;
  while(true){
    int ptr_to_first_of_word = command.find_first_of(ALPHABETIC);
    if(ptr_to_first_of_word == NOT_FOUND)
      break;
    int ptr_to_end_of_word =command.find_first_not_of(ALPHABETIC, ptr_to_first_of_word);
    if(ptr_to_end_of_word == NOT_FOUND)
    {
      word = command.substr(ptr_to_first_of_word);
      splitted_command.push_back(word);
      break;
    }
    word = command.substr(ptr_to_first_of_word, (ptr_to_end_of_word - ptr_to_first_of_word));
    splitted_command.push_back(word);
    command = command.substr(ptr_to_end_of_word);
  }
  return splitted_command;
}

void ShoppingCenter::add_user(vector<string> splitted_command)
{
	bool is_valid_to_add = true;
	for (int i = 0; i < users.size(); i++)
	{
		if(users[i]->is_the_same_person(splitted_command))
		{
			if(users[i]->is_seller == true && splitted_command[6] == "buyer")
			{
				users[i]->is_buyer = true;
				users[i]->add_money(stoi(splitted_command[5]));
				cout << OK_MSG << endl;
				return;
			}
			cout << (users[i]->is_buyer == true) << " " << (splitted_command[6] == "seller") << endl;
			if(users[i]->is_buyer == true && splitted_command[6] == "seller")
			{
				users[i]->is_seller = true;
				users[i]->add_money(stoi(splitted_command[5]));
				cout << OK_MSG << endl;
				return;
			}	
		}
		if(users[i]->is_the_same_username(splitted_command[3]) && (users[i]->is_seller && users[i]->is_buyer == false))
			is_valid_to_add = false;
	}
	if(is_valid_to_add)
	{
		Person* user = new Person(splitted_command);
		users.push_back(user);
		cout << OK_MSG << endl;
	}
	else
		cout << FAILED_MSG << endl;
}

void ShoppingCenter::add_goods(vector<string> splitted_command)
{
	for (int i = 0; i < users.size(); i++)
	{
		if(users[i]->is_the_same_username(splitted_command[1]) && (users[i]->is_seller == true))
			{
				Goods* goods = new Goods(splitted_command);
				users[i]->seller->add_goods(goods);
				cout << OK_MSG << endl;
				return;
			}		
	}
	cout << FAILED_MSG << endl;
}

void ShoppingCenter::swap_goods(Goods*& goods1, Goods*& goods2)
{
	Goods* a = goods1;
	goods1 = goods2;
	goods2 = a ;
}

bool ShoppingCenter::search_goods_sort(vector<Goods*>& all_goods)
{
	for (int i = 0; i < (all_goods.size() - 1); i++)
	{
		for (int j = 0; j < (all_goods.size() - 1 - i); j++)
		{
			if(all_goods[j]->get_count() < all_goods[j + 1]->get_count())
				swap_goods(all_goods[j], all_goods[j + 1]);
			else if(all_goods[j]->get_count() == all_goods[j + 1]->get_count())
			{
				if(all_goods[j]->get_price() > all_goods[j + 1]->get_price())
					swap_goods(all_goods[j], all_goods[j + 1]);
				else if(all_goods[j]->get_price() == all_goods[j + 1]->get_price())
				{
					if(all_goods[j]->get_seller_username()[0] > all_goods[j + 1]->get_seller_username()[0]) 
						swap_goods(all_goods[j], all_goods[j + 1]);
				}
			}
		}
	}
}

void ShoppingCenter::search_goods(vector<string> splitted_command)
{
	vector<Goods*> all_searches_goods;
	for (int i = 0; i < users.size(); i++)
	{
		vector<Goods*> founded_goods = users[i]->find_goods(splitted_command[1], stoi(splitted_command[2]));
		for (int j = 0; j < founded_goods.size(); j++)
			all_searches_goods.push_back(founded_goods[j]);
	}
	if(all_searches_goods.size() > 0)
		search_goods_sort(all_searches_goods);
	for (int i = 0; i < all_searches_goods.size(); i++)
	{
		cout << i+1 <<". " ;
		all_searches_goods[i]->print();
	}
}

void ShoppingCenter::sale(vector<string> splitted_command)
{
	bool is_real_buyer = false;
	bool is_real_seller = false;
	int seller_index;
	for (int i = 0; i < users.size(); i++)
	{
		if(users[i]->is_the_same_username(splitted_command[1]) && users[i]->is_buyer)
			is_real_buyer = true;
		if(users[i]->is_the_same_username(splitted_command[3]) && users[i]->is_seller)
		{
			is_real_seller = true;
			seller_index = i;	
		}
	}
	if((is_real_seller && is_real_buyer) == false)
	{
		cout << FAILED_MSG << endl;
		return;
	}
	bool suggested_successfully = users[seller_index]->seller->add_sale_suggestion(splitted_command[2], splitted_command[1]);
	if(suggested_successfully)
		cout << OK_MSG << endl;
	else
		cout << FAILED_MSG << endl;
}

void ShoppingCenter::add_special(vector<string> splitted_command)
{
	bool is_real_seller = false;
	int seller_index;
	for (int i = 0; i < users.size(); i++)
	{
		if(users[i]->is_the_same_username(splitted_command[1]) && (users[i]->seller != NULL))
		{
			is_real_seller = true;
			seller_index = i;	
		}
	}
	if(!is_real_seller)
	{
		cout << "IM here2 " << endl;
		cout << FAILED_MSG << endl;
		return;
	}
	bool added_successfully = users[seller_index]->seller->add_special(splitted_command[2]);
	if(added_successfully)
		cout << OK_MSG << endl;
	else
		cout << FAILED_MSG << endl;
	return;
}

void ShoppingCenter::remove_special(vector<string> splitted_command)
{
	bool is_real_seller = false;
	int seller_index;
	for (int i = 0; i < users.size(); i++)
	{
		if(users[i]->is_the_same_username(splitted_command[1]) && (users[i]->seller != NULL))
		{
			is_real_seller = true;
			seller_index = i;	
		}
	}
	if(!is_real_seller)
	{
		cout << FAILED_MSG << endl;
		return;
	}
	bool removed_successfully = users[seller_index]->seller->remove_special(splitted_command[2]);
	if(removed_successfully)
		cout << OK_MSG << endl;
	else
		cout << FAILED_MSG << endl;
	return;
}

void ShoppingCenter::add_money(vector<string> splitted_command)
{
	for (int i = 0; i < users.size(); i++)
	{
		if(users[i]->is_the_same_username(splitted_command[1]))
		{
			users[i]->add_money(stoi(splitted_command[2]));
			cout << OK_MSG << endl;
			return;
		}
	}
	cout << FAILED_MSG << endl;
}

void ShoppingCenter::buy(vector<string> splitted_command)
{
	Factor* factor;
	string buyer_username = splitted_command[1];
	if(splitted_command[4].find_first_of(',') != NOT_FOUND)
	{
		splitted_command[4] = splitted_command[4].substr(0, splitted_command[4].find_first_of(','));
		factor = new Factor(buyer_username, splitted_command[2], stoi(splitted_command[3]), splitted_command[4]); 
		string line;
		while(getline(cin,line))
		{
			vector<string> splitted_line = split_command(line);
			if(splitted_line[2].find_first_of(',') != NOT_FOUND)	
			{
				splitted_line[2] = splitted_line[2].substr(0, splitted_line[2].find_first_of(','));
				factor->add_goods(splitted_line[0], stoi(splitted_line[1]) , splitted_line[2]);
			}	
			else if(splitted_line[2].find_first_of(';') != NOT_FOUND)	
			{
				splitted_line[2] = splitted_line[2].substr(0, splitted_line[2].find_first_of(';'));
				factor->add_goods(splitted_line[0], stoi(splitted_line[1]) , splitted_line[2]);
				break;
			}
		}
	}
	else
	{
		splitted_command[4] = splitted_command[4].substr(0, splitted_command[4].find_first_of(';'));
		factor = new Factor(buyer_username, splitted_command[2], stoi(splitted_command[3]), splitted_command[4]); 				
	}
	int money_added_to_shoppingcenter = 0;
	if(factor->buy(users, money_added_to_shoppingcenter))
	{
		money =+ money_added_to_shoppingcenter ;
		factors.push_back(factor);
		cout << "Factor number " << factors.size() << endl;
		factor->print_factor(users);
		factor->decrease_num_of_goods(users);
	}
	else
		cout << FAILED_MSG << endl;
}

void ShoppingCenter::request(vector<string> splitted_command)
{
	Request* request;
	if(splitted_command[5].find_first_of(',') != NOT_FOUND)
	{
		splitted_command[5] = splitted_command[5].substr(0, splitted_command[5].find_first_of(','));
		request = new Request(splitted_command); 
		string line;
		while(getline(cin,line))
		{
			vector<string> splitted_line = split_command(line);
			if(splitted_line[2].find_first_of(',') != NOT_FOUND)	
			{
				splitted_line[2] = splitted_line[2].substr(0, splitted_line[2].find_first_of(','));
				request->add_goods(splitted_line[0], stoi(splitted_line[1]) , splitted_line[2]);
			}	
			else if(splitted_line[2].find_first_of(';') != NOT_FOUND)	
			{
				splitted_line[2] = splitted_line[2].substr(0, splitted_line[2].find_first_of(';'));
				request->add_goods(splitted_line[0], stoi(splitted_line[1]) , splitted_line[2]);
				break;
			}
		}
	}
	else
	{
		splitted_command[5] = splitted_command[5].substr(0, splitted_command[5].find_first_of(';'));
		request = new Request(splitted_command); 				
	}
	requests.push_back(request);
	cout << OK_MSG << endl;
}

void ShoppingCenter::print_request(string buyer_username)
{
	for (int i = 0; i < requests.size(); i++)
	{
		if(requests[i]->is_same_buyer(buyer_username))
		{
			cout << "Request " << (i + 1) << " " ;
			requests[i]->print();
		}
	}
}

void ShoppingCenter::print_factor(string buyer_username)
{
	for (int i = 0; i < factors.size(); i++)
	{
		if(factors[i]->is_same_buyer(buyer_username))
		{
			cout << "Factor " << (i + 1) << " " ;
			factors[i]->print_factor(users);
		}
	}
}

void ShoppingCenter::check_for_sale()
{
	for (int i = 0; i < users.size(); i++)
	{
		if(users[i]->seller != NULL)
		{
			users[i]->seller->check_sale_suggestions();	
		}
	}
}

void ShoppingCenter::sort_on_sale_goods(vector<Goods*> all_goods)
{
	for (int i = 0; i < (all_goods.size() - 1); i++)
	{
		for (int j = 0; j < (all_goods.size() - 1 - i); j++)
		{
			if(all_goods[j]->get_goods_name() > all_goods[j + 1]->get_goods_name())
				swap_goods(all_goods[j], all_goods[j + 1]);
			else if(all_goods[j]->get_goods_name() == all_goods[j + 1]->get_goods_name())
			{
				if(all_goods[j]->get_count() < all_goods[j + 1]->get_count())
					swap_goods(all_goods[j], all_goods[j + 1]);
				else if(all_goods[j]->get_count() == all_goods[j + 1]->get_count())
				{
					if(all_goods[j]->get_price() > all_goods[j + 1]->get_price()) 
						swap_goods(all_goods[j], all_goods[j + 1]);
					else if(all_goods[j]->get_price() == all_goods[j + 1]->get_price())
					{
						if(all_goods[j]->get_seller_username()[0] > all_goods[j + 1]->get_seller_username()[0])
							swap_goods(all_goods[j], all_goods[j + 1]);
					}
				}
			}
		}
	}	
}

void ShoppingCenter::search_sale()
{
	vector<Goods*> all_on_sale_goods;
	for (int i = 0; i < users.size(); i++)
	{
		if(users[i]->seller != NULL)
		{
			vector<Goods*> on_sale_goods = users[i]->seller->search_sale();	
			for (int j = 0; j < on_sale_goods.size(); j++)
				all_on_sale_goods.push_back(on_sale_goods[j]);
		}
	}
	if(all_on_sale_goods.size() > 0)
		sort_on_sale_goods(all_on_sale_goods);
	for (int i = 0; i < all_on_sale_goods.size(); i++)
	{
		cout << i + 1 << ". ";
		all_on_sale_goods[i]->print_goods();
	}
}

void ShoppingCenter::check_requests()
{
	for (int i = 0; i < requests.size(); i++)
	{
		Factor* factor = new Factor();
		factor->change_request_to_factor(requests[i]);
		 int money_added_to_shoppingcenter = 0;
		if(factor->buy(users, money_added_to_shoppingcenter))
		{
			money += money_added_to_shoppingcenter;
			factors.push_back(factor);
			cout << "Factor number " << factors.size() << endl;
			factor->print_factor(users);
		}
		else
		{
			if(factor->check_if_goods_existed(users))
				requests.erase(requests.begin() + i);
			else
				continue;
		}
	}
}

void ShoppingCenter::search_bestseller()
{
	vector<Goods*> all_bestsellers;
	for (int i = 0; i < users.size(); i++)
	{
		if(users[i]->seller != NULL)
		{
			vector<Goods*> bestsellers = users[i]->seller->search_bestsellers(); 
			for (int j = 0; j < bestsellers.size(); j++)
				all_bestsellers.push_back(bestsellers[j]);
		}
	}
	if(all_bestsellers.size() > 0)
		sort_on_sale_goods(all_bestsellers);
	for (int i = 0; i < all_bestsellers.size(); i++)
	{
		cout << i + 1 << ". ";
		all_bestsellers[i]->print_goods();
	}
}

void ShoppingCenter::process(string command)
{
	vector<string> splitted_command = split_command(command);
	check_for_sale();
	check_requests();
	if(splitted_command[0] == "add_user")
		add_user(splitted_command);
	else if(splitted_command[0] == "add_goods")
		add_goods(splitted_command);
	else if(splitted_command[0] == "search")
		search_goods(splitted_command);
	else if (splitted_command[0] == "buy")
		buy(splitted_command);
	else if(splitted_command[0] == "sale")
		sale(splitted_command);
	else if(splitted_command[0] == "add_special")
		add_special(splitted_command);
	else if(splitted_command[0] == "remove_special")
		remove_special(splitted_command);
	else if(splitted_command[0] == "add_money")
		add_money(splitted_command);
	else if(splitted_command[0] == "request")
		request(splitted_command);
	else if(splitted_command[0] == "search_sale")
		search_sale();
	else if(splitted_command[0] == "print_request")
		print_request(splitted_command[1]);
	else if(splitted_command[0] == "search_bestseller")
		search_bestseller();
	else if(splitted_command[0] == "print_factor")
		print_factor(splitted_command[1]);
	else
		cout << FAILED_MSG << endl;
}