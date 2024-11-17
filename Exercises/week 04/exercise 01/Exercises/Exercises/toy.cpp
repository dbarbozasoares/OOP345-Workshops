#include "toy.h"
#include <string>

namespace seneca {
	Toy::Toy() : m_id(0), m_name(""), m_quantity(0), m_price(0.0), m_sales_total_tax(0.0) {}

	std::string Toy::getName() const { return m_name; }

	int Toy::getQuant() const { return m_quantity; }

	int Toy::getId() const { return m_id; }

	double Toy::getPrice() const { return m_price; }

	double Toy::getTotalTax() const { return m_sales_total_tax; }

	double Toy::getSubTotal() const { return getPrice() * getQuant(); }

	void Toy::setSalesTax(double value) { m_sales_total_tax = value; }

	int Toy::getColonPos(const std::string str)
	{
		return str.find(":", 1);
	}

	void Toy::update(int numItems)
	{
		if (numItems && numItems > 0) {
			m_quantity = numItems;
		}
	}

	Toy::Toy(const std::string& toy)
	{
		std::string str = toy;
		int col_pos;


		// while finds space remove it
		while (str.find(" ", 1) != std::string::npos) {
			int pos = str.find(" ", 1);
			str.erase(pos, 1);
		}

		col_pos = getColonPos(str); // find colon
		m_id = std::stoi(str.substr(0, col_pos));

		str.erase(0, col_pos - 1);//remove id and colon

		col_pos = getColonPos(str); // find colon
		m_name = str.substr(0, col_pos);

		str.erase(0, col_pos - 1);

		col_pos = getColonPos(str);
		update(std::stoi(str.substr(0, col_pos)));
		
		str.erase(0, col_pos - 1);

		col_pos = getColonPos(str);
		m_price = stod(str.substr(0, col_pos));

		setSalesTax((m_price * m_quantity) * HST_TAX);

	}


}