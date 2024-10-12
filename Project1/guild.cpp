/*/////////////////////////////////////////////////////////////////////////
						 Workshop 2
Full Name  : Diego Barboza Soares
Student ID#: 145820239
Email      : dbarboza-soares@myseneca.ca
Section    : NCC
Date       : 12th Octuber 2024

Authenticity Declaration:

I have done all the coding by myself and only copied the code that my
professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/
#include "guild.h"

namespace seneca {
	//  parametized constructor
	Guild::Guild(const char* name) : m_guild_name(name), m_members(nullptr), m_total_members(0) {}

	// copy constructor
	Guild::Guild(const Guild& src)
	{
		m_guild_name = src.m_guild_name;
		m_total_members = src.m_total_members;
		m_members = new Character * [m_total_members]; // create a new array of pointers type Character

		if (m_total_members > 0) // make sure we have members to be transfered
		{
			for (int i = 0; i < m_total_members; i++)
			{
				m_members[i] = src.m_members[i]; // shallow copy of pointers
			}
		}
		else
		{
			m_members = nullptr; // if total members is 0, set it to safe state
		}
	}
	// move constructor
	Guild::Guild(Guild&& src) noexcept
	{
		m_members = src.m_members;
		m_total_members = src.m_total_members;
		m_guild_name = std::move(src.m_guild_name);

		src.m_members = nullptr;
		src.m_total_members = 0;
	}

	// copy assignment operator
	Guild& Guild::operator=(const Guild& src)
	{
		if (this != &src) { // checks self assignment

			m_guild_name = src.m_guild_name;
			m_total_members = src.m_total_members;

			delete[] m_members; // delete current resources

			m_members = new Character * [m_total_members]; // create new address of pointers for current members array

			for (int i = 0; i < m_total_members; i++)
			{
				m_members[i] = src.m_members[i];
			}
		}
		return *this;
	}

	// move assignment operator
	Guild& Guild::operator=(Guild&& src) noexcept
	{
		if (this != &src) { // checks self assignment
			for (int i = 0; i < m_total_members; i++)
			{
				delete m_members[i]; // delete each member individually
			}
			delete[] m_members; // delete whole array
			m_members = nullptr; // set to a safe empty state

			m_members = src.m_members;
			m_total_members = src.m_total_members;
			m_guild_name = std::move(src.m_guild_name); // transfer ownership from name

			src.m_members = nullptr; // set to a safe state
			src.m_total_members = 0;
		}
		return *this; // return new object
	}

	// destructor
	Guild::~Guild()
	{
		delete[] m_members;
		m_members = nullptr;
	}

	std::string Guild::getGuildName() const { return m_guild_name; }

	// add a new member into a guild
	void Guild::addMember(Character* c)
	{
		if (c != nullptr) { // make sure we receive a valid character
			bool character_exists = false;

			if (m_total_members > 0) { // if our members array is empty, skip this
				for (int i = 0; i < m_total_members; i++)
				{
					if (m_members[i]->getName() == c->getName()) {
						character_exists = true;
						i = m_total_members;
					}
				}
			}

			if (!character_exists) { // make sure we dont add same member twice

				Character** tmp_array = new Character * [m_total_members + 1]; // create new array of pointers with new size

				for (int i = 0; i < m_total_members; i++)
				{
					tmp_array[i] = m_members[i]; // get each pointer reference as shallow copy
				}
				delete[] m_members; // delete whole array

				c->setHealthMax(c->getHealthMax() + HP_BONUS_GUILD); // set updated health
				c->setHealth(c->getHealthMax()); // fill up new member health

				tmp_array[m_total_members] = c; // stores reference for new membe
				m_members = tmp_array; // point old array to new array with updated size
				m_total_members++; // updates total members
			}
		}
	}

	// remove member from a guild
	void Guild::removeMember(const std::string& c)
	{
		int idx_deleted = -1; // checker to make sure name exists
		for (int i = 0; i < m_total_members; i++)
		{
			if (m_members[i]->getName() == c) {
				m_members[i]->setHealth(m_members[i]->getHealthMax()- HP_BONUS_GUILD);// reduce HP since leaving guild
				m_members[i]->setHealthMax(m_members[i]->getHealth());
				
				idx_deleted = i; // saves index to update array next step
			}
		}
		if (idx_deleted != -1) { // if character exists
			Character** tmp_array = new Character*[m_total_members - 1]; // set new size for current member array
			for (int i = 0, j = 0; i < m_total_members; i++) {
				if (i != idx_deleted) { // make sure we dont copy the index deleted
					tmp_array[j++] = m_members[i]; // transfer each reference
				}
			}
			delete[] m_members; // delete whole array (NOT POINTERS)
			m_members = tmp_array; // points array to a new address with members updated
			m_total_members--; // updates total members
		}
	}

	// return member pointer from a given index
	Character* Guild::operator[](size_t idx) const { return (int)idx >= m_total_members ? nullptr : m_members[idx]; }

	// display all guild members individually
	void Guild::showMembers() const
	{
		if (m_members == nullptr) {
			std::cout << "No guild." << std::endl;
 		}
		else
		{
			std::cout << "[Guild] " << getGuildName() << std::endl;
			for (int i = 0; i < m_total_members; i++)
			{
				std::cout << "    " << i+1 << ": " << *m_members[i] << std::endl;
			}
		}
	}


}