#include "book.h"
#include <iomanip>
#include "settings.h"
#include <sstream>

namespace seneca {
	void Book::display(std::ostream& out) const
	{
        if (g_settings.m_tableView)
        {
            out << "B | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << this->m_country << " | ";
            out << std::setw(4) << this->getYear() << " | ";
            out << std::left;
            if (g_settings.m_maxSummaryWidth > -1)
            {
                if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
                    out << this->getSummary();
                else
                    out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
            }
            else
                out << this->getSummary();
            out << std::endl;
        }
        else
        {
            size_t pos = 0;
            out << this->getTitle() << " [" << this->getYear() << "] [";
            out << m_author << "] [" << m_country << "] [" << m_price << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size())
            {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
	}
    Book* Book::createItem(const std::string& strBook)
    {
        std::stringstream line(strBook);
        string str;
        string author, title, country, summary;
        double price = 0.0;
        unsigned short year = 0;
        if (strBook[0] == '#' || strBook.empty()) {
            throw "Not a valid book.";
        }
        // Read fields from CSV line
        if (getline(line, str, ',')) {
            trim(str);
            author = str;  // Set author
        }

        if (getline(line, str, ',')) {
            trim(str);
            title = str;  // Set title
        }

        if (getline(line, str, ',')) {
            trim(str);
            country = str;  // Set country
        }

        if (getline(line, str, ',')) {
            trim(str);
            price = std::stod(str);  // Set price
        }

        if (getline(line, str, ',')) {
            trim(str);
            year = std::stoi(str);  // Set year
        }

        if (getline(line, str)) {
            trim(str);
            summary = str;  // Set summary
        }
        Book* temp_book = new Book(author,title,summary,year,country,price);

        return temp_book;
    }
}