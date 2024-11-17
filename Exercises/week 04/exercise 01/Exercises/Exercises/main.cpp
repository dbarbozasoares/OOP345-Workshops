#include <iostream>
#include <string>
using namespace std;

int main() {

	string str = "1000121  :  Red Bike:1  :  89.99";
	string res = "";
	string name = "";
	int id;
	double price;
	int quant;

	while (str.find(" ", 1) != std::string::npos) {
		int pos = str.find(" ", 1);
		str.erase(pos, 1);
	}


	int pos = str.find(":");
	res = str.substr(0, pos);
	id = stoi(res);

	str.erase(0, pos + 1);

	pos = str.find(":");
	name = str.substr(0, pos);

	str.erase(0, pos + 1);

	pos = str.find(":");
	res = str.substr(0, pos);
	quant = stoi(res);

	str.erase(0, pos + 1);

	price = stod(str);

	cout << id << " " << name << " " <<  quant << " " << price;



	return 0;
}