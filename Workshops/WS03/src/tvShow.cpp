#include "tvShow.h"
#include <iomanip>
#include "settings.h"
#include <sstream>
#include <algorithm>
#include <numeric>
#include <list>

namespace seneca {

    void TvShow::display(std::ostream& out) const
    {
        if (g_settings.m_tableView)
        {
            out << "S | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << this->m_episodes.size() << " | ";
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
            out << this->getTitle() << " [" << this->getYear() << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size())
            {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            for (auto& item : m_episodes)
            {
                out << std::setfill('0') << std::right;
                out << "    " << 'S' << std::setw(2) << item.m_season
                    << 'E' << std::setw(2) << item.m_numberInSeason << ' ';
                if (item.m_title != "")
                    out << item.m_title << '\n';
                else
                    out << "Episode " << item.m_numberOverall << '\n';

                pos = 0;
                while (pos < item.m_summary.size())
                {
                    out << "            " << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
                    pos += g_settings.m_maxSummaryWidth - 8;
                }
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
    }
    TvShow* TvShow::createItem(const std::string& strShow)
    {
        // ID,TITLE,YEAR,SUMMARY
        // Use trim() from MediaItem to trim strings
        int year = 0;
        std::string summ, title, str, id;
        std::stringstream ss(strShow);

        if (strShow[0] == '#' || strShow.empty()) {
            throw "Not a valid show.";
        }

        getline(ss, str, ',');
        MediaItem::trim(str);
        id = str;
          
        getline(ss, str, ',');
        MediaItem::trim(str);
        title = str;

        getline(ss, str, ',');
        MediaItem::trim(str);
        year = std::stoi(str);

        getline(ss, str);
        MediaItem::trim(str);
        summ = str;

        return new TvShow(title, summ, static_cast<unsigned short>(year), id); // assign new tvShow and return it
    }
    
    double TvShow::getEpisodeAverageLength() const
    {
        size_t total_ep = std::count_if(m_episodes.begin(), m_episodes.end(), [](const TvEpisode& episode) {return episode.m_length > 0; }); // checks how many episodes we have making sure all of them have time

        int total_seconds = std::accumulate(m_episodes.begin(), m_episodes.end(), 0, [](int accumulate, const TvEpisode& episode) {return accumulate + episode.m_length; });

        return static_cast<double>(total_seconds) / total_ep;
    }
    std::list<std::string> TvShow::getLongEpisodes() const
    {
        std::list<std::string> long_episodes;

        for (const auto& episode : m_episodes) {
            if (episode.m_length > 3600) {
                long_episodes.push_back(episode.m_title);
            }
        }

        return long_episodes;
    }
   
    const std::string TvShow::getId()
    {
        return m_id;
    }

}