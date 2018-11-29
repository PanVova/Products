#include "Products.h"
#include "sqlite3.h"
#include <cstdlib>
Products::Products()
{
	//load from db
	connect_to_database();
}

void Products::add_all_to_db() 
{
	sqlite3* DB;
	sqlite3_stmt *res;
	int exit = 0;
	exit = sqlite3_open("Products.db", &DB);
	char* messaggeError;
	const char *cstr = "0";
	string sql("Delete from Products ");
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	if (exit == SQLITE_BUSY )
	{
		cout << "IS USING BY SOMEONE" << endl;
	}
	if (exit != SQLITE_OK) {
		cerr << "Error delete : " << messaggeError <<  endl;
		sqlite3_free(messaggeError);
	}
	else
		cout << "Deletion Successfully!" << endl;

	string sql1("INSERT INTO Products VALUES(@id, @name, @price );");
	sqlite3_prepare_v2(DB, sql1.c_str(), -1, &res, 0);
	for (int i=0;i<products.size();i++) 
	{
		cstr = products[i].first.c_str();
		sqlite3_prepare_v2(DB, sql1.c_str(), -1, &res, 0);
		int id = sqlite3_bind_parameter_index(res, "@id");
		int name = sqlite3_bind_parameter_index(res, "@name");
		int price = sqlite3_bind_parameter_index(res, "@price");
		int value = 5;
		exit = sqlite3_bind_int(res, id, i);
		exit = sqlite3_bind_text(res, name, cstr, -1, 0);
		exit = sqlite3_bind_int(res, price, products[i].second);
	}
	
	if (exit != SQLITE_OK) {
		cerr << "Error Insert: " << messaggeError  << endl;
		sqlite3_free(messaggeError);
	}
	else
		cout << "Records inserted Successfully!" << endl;
	sqlite3_step(res);
	sqlite3_finalize(res);
	sqlite3_close(DB);
	system("pause");
}

void Products::connect_to_database() 
{
	char* name;
	char* price;
	char *zErrMsg = 0;
	char *sql = "SELECT * FROM Products WHERE id = ?;";
	sqlite3_stmt *res;
	sqlite3 *db;

	sqlite3_open("Products.db", &db);
	sqlite3_prepare_v2(db, sql, -1, &res, 0);
	int count = sqlite3_column_count(res);

	for (int i = 1;i<=count;i++) {
		sqlite3_bind_int(res, 1, i);
		int step = sqlite3_step(res);
		if (step == SQLITE_ROW) {
			name = (char *)sqlite3_column_text(res, 1);
			price = (char *)sqlite3_column_text(res, 2);
			products.push_back(make_pair(string(name), atoi(price)));
		}
	}
	sqlite3_finalize(res);
	sqlite3_close_v2(db);
}


void Products::add_product()
{
	pair<string, int> product;
	string n = " ";
	int p = 0;
	cout << "Enter a name of product : ";
	cin >> n;
	transform(n.begin(), n.end(), n.begin(), ::tolower);
	vector<pair<string, int>>::iterator it = find_product(n);
	if (it == products.end())
	{
		product.first = n;
		cout << "Enter a price  : ";
		cin >> p;
		product.second = p;
		products.push_back(product);
	}
	else if (it != products.end()) 
	{
		cout << "This product is already exists" << endl;
	}
}

void Products::view_products()
{
	for (int i = 0; i<products.size(); i++)
	{
		cout << products[i].first << " " << products[i].second << endl;
	}
}

vector<pair<string, int>>::iterator Products::find_product(string name)
{

	transform(name.begin(), name.end(), name.begin(), ::tolower);
	auto it = find_if(products.begin(), products.end(), [&name](const pair<string, int>& element) { return element.first == name; });
	return it;
}

void Products::edit_product() 
{
	string name = " ";
	cout << "Enter a name of product:";
	cin >> name;
	vector<pair<string, int>>::iterator it = find_product(name);
	if (it != products.end())
	{
		cout << "What do you want to change 1)Name 2)Price : ";
		int answer = 0;
		cin >> answer;
		if (answer == 1)
		{
			string new_name = " ";
			cin >> new_name;
			transform(new_name.begin(), new_name.end(), new_name.begin(), ::tolower);
			it->first = new_name;
		}
		else if (answer == 2)
		{
			int new_name = 0;
			cin >> new_name;
			it->second = new_name;
		}
	}
	
}

void Products::delete_product() 
{
	string name = " ";
	cout << "Enter a name of product:";
	cin >> name;
	vector<pair<string, int>>::iterator it = find_product(name);
	if (it != products.end())
	{
		products.erase(it);
	}
}

int Products::sum() 
{
	cout << "Enter a names of products:" << endl;
	string name = " ";
	vector<string> names;
	while (true) 
	{
		cin >> name;
		transform(name.begin(), name.end(), name.begin(), ::tolower);
		names.push_back(name);
		if (name == "stop")
		{
			break;
		}
	}
	int sum = 0;
	for (int i=0;i<names.size();i++) 
	{
		auto it = find_product(names[i]);
		if (it != products.end())
		{
			sum += it->second;
		}
		
	}
	return sum;
}


Products::~Products()
{
}
