#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class Products
{
	
private:
	vector <pair<string, int>> products;
	vector<pair<string, int>>::iterator find_product(string name);
	void connect_to_database();
public:

	int sum();
	void add_product();
	void view_products();
	void edit_product();
	void delete_product();
	void add_all_to_db();

	Products();
	~Products();
};

