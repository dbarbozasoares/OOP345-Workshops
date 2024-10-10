#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H
#include "character.h"

namespace seneca {

	// This is a composition class (It owns characters pointers)
	class Team {
		std::string m_team_name; // team name
		Character** m_members; // array of pointers that points to a character
		int m_total_members;
	public:
		Team(const char* name); // parametized constructor
		Team(const Team& t); // Copy constructor
		Team(Team&& t) noexcept; // Move operator
		Team& operator=(const Team& t); // copy assignment operator
		Team& operator=(Team&& t) noexcept; // move assignment operator
		std::string getTeamName() const; // returns team name
		int getTotalMembers() const; // returns total members for a team
		void addMember(const Character* c); // add new member into team
		void removeMember(const std::string& c); // remove a member from a team
		Character* operator[](size_t idx) const; // return a member from given index
		void showMembers() const; // display all members individually
		~Team(); // destructor
	};
}
#endif // !SENECA_TEAM_H
