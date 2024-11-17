#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H
#include "mediaItem.h"
#include <string>
#include <iostream>
using std::string;

namespace seneca {
	class Movie : public MediaItem{
		Movie() : MediaItem("", "", 0) {};
		Movie(string title, string summary, unsigned int year) : MediaItem(title, summary, year) {};

	public:
		void display(std::ostream& out) const override;
		static Movie* createItem(const std::string& strMovie);
	};
}
#endif // !SENECA_MOVIE_H
