#ifndef SENECA_TOY_H
#define SENECA_TOY_H
#include <iostream>
#include <iomanip>
namespace seneca {
	extern const int HST_TAX = 13;
	class Toy {
		unsigned int m_id;
		std::string  m_name;
		int m_quantity;
		double m_price;
		double m_sales_total_tax;
	public:
		Toy();
		std::string getName() const;
		int getQuant() const;
		int getId() const;
		double getPrice() const;
		double getTotalTax() const;
		double getSubTotal() const;
		void setSalesTax(double value);
		int getColonPos(const std::string str);
		void update(int numItems);
		Toy(const std::string& toy);

		friend std::ostream& operator<<(std::ostream&, const Toy&);
	};

	std::ostream& operator<<(std::ostream& ostr, const Toy& toy) {
		ostr << std::right << std::setfill('0') << std::setw(8) << toy.getId() << " : "
			<< std::setfill('.') << std::setw(24) << toy.getName() << " : "
			<< std::setfill(' ') << std::setw(2) << toy.getQuant() << " : "
			<< std::setw(6) << std::fixed << std::setprecision(2) << toy.getPrice() << " : "
			<< std::setw(7) << toy.getSubTotal() << " : "
			<< std::setw(6) << toy.getTotalTax() << " : "
			<< std::setw(7) << (toy.getSubTotal() + toy.getTotalTax());
		return ostr;
	}
}

#endif // !SENECA_TOY_H

