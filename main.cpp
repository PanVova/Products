#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include "Products.h"
using namespace std;
int menu() 
{
	cout << "\nWhat do you want to do ?\n" << "1)Add product\n2)Edit product\n3)Delete product\n4)View all products\n5)Sum all of the named products\n6)Exit from program\n";
	int answer = 0;
	cin >> answer;
	return answer;
}


int main() 
{
	Products * products = new Products();
	while (true)
	{
		int number = menu();
		if (number == 1)
		{
			products->add_product();
		}
		else if (number == 2)
		{
			products->edit_product();
		}
		else if (number == 3)
		{
			products->delete_product();
		}
		else if (number == 4)
		{
			products->view_products();
		}
		else if (number == 5)
		{
			cout <<"Total price of your named products is " <<  products->sum() << endl;
		}
		else if (number == 6)
		{
			products->add_all_to_db();
			exit(0);
		}
	}
	system("pause");
}