#include <iostream>
#include "shoppingcenter.hpp"

using namespace std;

int main()
{
	ShoppingCenter shoppingcenter = ShoppingCenter();
	string command;
	while(getline(cin, command))
		shoppingcenter.process(command);
	return 0;
}