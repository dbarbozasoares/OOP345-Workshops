#include "collection.h"
#include <algorithm>
#include <sstream>

namespace seneca {
	const std::string& Collection::name() const
	{
		return m_collection_name;
	}
	size_t Collection::size() const
	{
		return m_media_items.size();
	}
	void Collection::setObserver(void(*observer)(const Collection&, const MediaItem&))
	{
		this->callback = observer;
	}
	Collection& Collection::operator+=(MediaItem* item)
	{
		auto it = std::find_if(m_media_items.begin(), m_media_items.end(), [item](const MediaItem* item_in_col) {
			return item->getTitle() == item_in_col->getTitle();
			});

		// If not found, add it to the collection
		if (it == m_media_items.end()) {
			m_media_items.push_back(item);  // Add the item to the collection

			// Trigger the callback if it's set
			if (callback) {
				callback(*this, *item);
			}
		}
		return *this;
	}
	MediaItem* Collection::operator[](size_t idx) const
	{

		if (idx > size()) {
			throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(size()) + "] items.");
		}
		return m_media_items[idx];
	}
	MediaItem* Collection::operator[](const std::string& title) const
	{
		MediaItem* media = nullptr;
		if (!title.empty()) {
			for (auto& item : m_media_items) {
				if (item->getTitle() == title) {
					media =  item; // assign the matching item if found
					break;
				}
			}
		}
		return media;
	}
	void Collection::removeQuotes()
	{
		std::for_each(m_media_items.begin(), m_media_items.end(), [](MediaItem* item) {
			std::string title = item->getTitle();
			title.erase(std::remove(title.begin(), title.end(), '"'),title.end());
			item->setTitle(title);

			std::string summ = item->getSummary();
			std::istringstream ss(summ);
			std::string word;
			std::string new_summary;

			while (ss >> word) {
				word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
				new_summary += word + " ";
			}
			if (!new_summary.empty()) {
				new_summary.pop_back();
			}
			item->setSummary(new_summary);
		});
	}
	void Collection::sort(const std::string& field)
	{
		std::sort(m_media_items.begin(), m_media_items.end(), [field](MediaItem* item1, MediaItem* item2) {
			if (field == "title") {
				return item1->getTitle() < item2->getTitle();
			}
			else if (field == "year") {
				return item1->getYear() < item2->getYear();
			}
			else {
				return item1->getSummary() < item2->getSummary();
			}
		});
	}
	std::ostream& operator<<(std::ostream& ostr, const Collection& col) {
		for (size_t i = 0; i < col.size(); i++)
		{
			col[i]->display(ostr);
		}
		return ostr;
	}
	Collection::~Collection()
	{
		for (auto item : m_media_items) {
			delete item;
		}
		m_media_items.clear();
		callback = nullptr;
	}
}
