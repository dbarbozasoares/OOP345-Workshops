#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H
#include "mediaItem.h"
#include <vector>
#include <iostream>
#include <algorithm>

namespace seneca {
	class Collection{
		std::string m_collection_name;
		std::vector<MediaItem*> m_media_items;
		void(*callback)(const Collection&, const MediaItem&);
	public:
		Collection(const std::string& name) : m_collection_name(name), m_media_items(), callback(nullptr) {};
		Collection(const Collection&) = delete;
		Collection& operator=(const Collection&) = delete;
		const std::string& name() const;
		size_t size() const;
		void setObserver(void (*observer)(const Collection&, const MediaItem&));
		Collection& operator+=(MediaItem* item);
		MediaItem* operator[](size_t idx) const;
		MediaItem* operator[](const std::string& title) const;
		void removeQuotes();
		void sort(const std::string& field);
		friend std::ostream& operator<<(std::ostream& ostr, const Collection& col);
		~Collection();
	};
}
#endif // !SENECA_COLLECTION_H
