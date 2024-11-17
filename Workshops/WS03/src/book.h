#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H
#include "mediaItem.h"
#include <string>
#include <iostream>
using std::string;
namespace seneca {
	class Book : public MediaItem {
		string m_author;
		string m_country;
		double m_price;
		Book() : MediaItem("", "", 0), m_author(""), m_country(""), m_price(0.00) {};
		Book(string author, string title, string summary, unsigned int year, string country, double price) : MediaItem(title, summary, year), m_author(author), m_country(country), m_price(price) {};

	public:
		void display(std::ostream& out) const override;
		static Book* createItem(const std::string& strBook);
	};
}
#endif // !SENECA_BOOK_H
