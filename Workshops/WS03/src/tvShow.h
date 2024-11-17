#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H
#include <list>
#include <vector>
#include "mediaItem.h"
#include <string>
#include <sstream>
#include "collection.h"

namespace seneca {

	class TvShow : public MediaItem {
		struct TvEpisode
		{
			const TvShow* m_show{};
			unsigned short m_numberOverall{};
			unsigned short m_season{};
			unsigned short m_numberInSeason{};
			std::string m_airDate{};
			unsigned int m_length{};
			std::string m_title{};
			std::string m_summary{};
		};

		std::string m_id;
		std::vector<TvEpisode> m_episodes;
		TvShow(std::string title, std::string summ, unsigned short year, std::string id) : MediaItem(title, summ,year), m_id(id) {};
	public:
		void display(std::ostream& out) const override;
		static TvShow* createItem(const std::string& strShow);
		double getEpisodeAverageLength() const;
		std::list<std::string> getLongEpisodes() const;
		const std::string getId();
		template<typename Collection_t>
		static void addEpisode(Collection_t& col, const std::string& strEpisode);
	};

	template<typename Collection_t>
	inline void TvShow::addEpisode(Collection_t& col, const std::string& strEpisode)
	{
		// ID, EP_NO OVERALL, SEASON_NO, EP_IN_SEAS, AIR_DATE, LENGTH, TITLE, SUMMARY

		std::string id, air_date, title, summary, str;
		int overall, season_no = 0, ep_in_seas = 0, length = 0;
		std::stringstream ss(strEpisode);

		try {
			if (strEpisode[0] == '#' || strEpisode.empty()) {
				throw "Not a valid episode.";
			}
			else {

				if (getline(ss, str, ',')) {
					MediaItem::trim(str);
					id = str;
				}
				if (getline(ss, str, ',')) {
					MediaItem::trim(str);
					overall = std::stoi(str);
				}

				if (getline(ss, str, ',')) {
					MediaItem::trim(str);
					if (str.empty()) {
						season_no = 1; // if season not declared, assume season 1
					}
					else {
						season_no = std::stoi(str);
					}
				}

				if (getline(ss, str, ',')) {
					MediaItem::trim(str);
					ep_in_seas = std::stoi(str);
				}

				if (getline(ss, str, ',')) {
					MediaItem::trim(str);
					air_date = str;
				}

				if (!getline(ss, str, ','));
				MediaItem::trim(str);
				std::replace(str.begin(), str.end(), '.', ':'); // handles '.' and ':' for time separator
				std::stringstream time_ss(str);
				if (getline(time_ss, str, ':')) length += std::stoi(str) * 3600; // hours
				if (getline(time_ss, str, ':')) length += std::stoi(str) * 60;   // minutes
				if (getline(time_ss, str)) length += std::stoi(str);

				if (getline(ss, str, ',')) {
					MediaItem::trim(str);
					title = str;
				}

				if (getline(ss, str)) {
					MediaItem::trim(str);
					summary = str;
				}
				for (size_t i = 0; i < col.size(); i++)
				{
					 TvShow* target_show = dynamic_cast<TvShow*>(col[i]);

					if (target_show != nullptr && target_show->getId() == id) { // if TV show is located, create a temp episode and push into TV 
						TvEpisode new_episode;
						new_episode.m_numberOverall = overall;
						new_episode.m_airDate = air_date;
						new_episode.m_length = length;
						new_episode.m_numberInSeason = ep_in_seas;
						new_episode.m_season = season_no;
						new_episode.m_show = target_show;
						new_episode.m_title = title;
						new_episode.m_summary = summary;
						target_show->m_episodes.push_back(new_episode);
					}
				}
			}
		}
		catch (std::invalid_argument& e) {
			std::cout << e.what() << std::endl;
		}
	}
}
#endif // !SENECA_TVSHOW_H
