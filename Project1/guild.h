#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H
#define HP_BONUS_GUILD 300
#include "character.h"
#include "characterTpl.h"
namespace seneca {
	// this is an aggregation class (it just holds a pointer, it doesnt delete any original pointer)
	class Guild {
		std::string m_guild_name; // guild name
		Character** m_members; // hold pointers from team class
		int m_total_members; // total members in guild
	public:
		Guild(const char* name); // parametized constructor
		Guild(const Guild& src); // copy constructor
		Guild(Guild&& src) noexcept; // move constructor
		Guild& operator=(const Guild& src); // move assignment operator
		Guild& operator=(Guild&& src) noexcept; // move assignment operator
		~Guild(); // destructor
		std::string getGuildName() const; // returns guild name
		void addMember(Character* c); // add a member into a guild
		void removeMember(const std::string& c); // remove member from a guild
		Character* operator[](size_t idx) const; // return object from given index
		void showMembers() const; // display members individually
	};
}
#endif // !SENECA_GUILD_H
