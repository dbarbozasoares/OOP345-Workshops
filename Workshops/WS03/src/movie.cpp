#include "movie.h"
#include <iomanip>
#include "settings.h"
#include <sstream>

namespace seneca {
	void Movie::display(std::ostream& out) const
	{
        if (g_settings.m_tableView)
        {
            out << "M | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(9) << this->getYear() << " | ";
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
            out << this->getTitle() << " [" << this->getYear() << "]\n";
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
    // TITLE,YEAR,SUMMARY
    Movie* Movie::createItem(const std::string& strMovie)
    {
        // using trim() from base class
        string title, summary;
        unsigned int year;
        std::stringstream ss(strMovie);
        string str;

        if (strMovie[0] == '#' || strMovie.empty()) {
            throw "Not a valid movie.";
        }

        std::getline(ss, str, ',');
        trim(str);
        title = str;

        std::getline(ss, str, ',');
        trim(str);
        year = std::stoi(str);

        std::getline(ss, str);
        trim(str);
        summary = str;

        Movie* movie = new Movie(title, summary, year);

        return movie;
    }
}