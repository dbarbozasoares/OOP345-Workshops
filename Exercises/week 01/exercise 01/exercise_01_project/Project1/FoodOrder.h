#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H
#include <string.h>
#include <string>
#include <fstream>
using namespace std;

namespace seneca {

	double g_taxrate;
	double g_dailydiscount;

	class FoodOrder {
		char customerName[10];
		const char* foodDescription;
		double foodPrice;
		bool isDailySpecial;

	public:
		istream& read(istream&);
	};
}
#endif // !SENECA_FOODORDER_H

