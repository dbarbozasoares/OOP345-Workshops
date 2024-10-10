#include "team.h"

namespace seneca {
	// Parametized constructor
	Team::Team(const char* name) : m_members(nullptr), m_total_members(0)
	{
		m_team_name = name != nullptr ? name : ""; // if name is nullptr, set it to empty safe state
	}

	// copy constructor (calls move assignment operator)
	Team::Team(const Team& src)
	{
		m_total_members = src.m_total_members;
		m_team_name = src.m_team_name;

		m_members = new Character * [m_total_members];

		for (int i = 0; i < m_total_members; i++)
		{
			m_members[i] = src.m_members[i]->clone(); // late binding type of character
		}
	}

	// move constructor (calls move assignment operator)
	Team::Team(Team&& src) noexcept
	{
		m_members = src.m_members;
		m_team_name = std::move(src.m_team_name); // transfer name ownership and set it to a safe state
		m_total_members = src.m_total_members;

		// make sure to set source to safe empty state
		src.m_members = nullptr;
		src.m_total_members = 0;
	}

	// move assginment operator
	Team& Team::operator=(const Team& src)
	{
		if (this != &src) // check self assignment
		{
			if (m_members != nullptr) { // make sure we have members in source team
				for (int i = 0; i < m_total_members; i++)
				{
					delete m_members[i]; // delete each current member pointer individually
				}
				delete[] m_members; // delete the whole member array
			}
			m_total_members = src.m_total_members;
			m_team_name = src.m_team_name;

			m_members = new Character * [m_total_members]; // create new address for current team members

			for (int i = 0; i < m_total_members; i++)
			{
				m_members[i] = src.m_members[i]->clone(); // late binding type of character to converts to (Archer,Barbarian or Rogue)
			}
		}
		return *this;
	}

	Team& Team::operator=(Team&& src) noexcept
	{
		if (this != &src) // check self assignment
		{
			for (int i = 0; i < m_total_members; i++)
			{
				delete m_members[i]; // delete each pointer individually
			}
			delete[] m_members; // delete whole array

			m_members = src.m_members;
			m_team_name = std::move(src.m_team_name); // transfer name ownership and set it to a safe state
			m_total_members = src.m_total_members;

			// make sure to set source to safe empty state
			src.m_members = nullptr;
			src.m_total_members = 0;
		}
		return *this;
	}

	std::string Team::getTeamName() const { return m_team_name; }

	int Team::getTotalMembers() const { return m_total_members; }

	// add new member into a team
	void Team::addMember(const Character* c)
	{
		if (c != nullptr)
		{
			bool char_exists = false; // make sure we dont add same charcter twice
			for (int i = 0; i < m_total_members; i++)
			{
				if (m_members[i]->getName() == c->getName()) 
				{
					char_exists = true; // set character found to true
					i = m_total_members; // exits loop
				}
			}

			if (!char_exists) // if character doesnt exists, add it into new memory address with new size
			{
				Character** tmp_array = new Character * [m_total_members + 1]; // create new array with new size

				for (int i = 0; i < m_total_members; i++)
				{
					tmp_array[i] = m_members[i]; // tansfer the pointers and do not create a new clone so we dont loose reference
				}
				delete[] m_members; // free mem from current array
				tmp_array[m_total_members] = c->clone(); // add new member into lat position

				m_members = tmp_array; // points team array to new memory address
				m_total_members++; // updated total members counter
			}
		}
	}

	// remove a mmember by comparing parameter name
	void Team::removeMember(const std::string& c)
	{
		if (c != "") { // make sure we do not receive an empty name
			Character** tmp_array = new Character * [m_total_members - 1];
			int idx_deleted = -1; // if not found, doesnt change anything on our current array
			for (int i = 0; i < m_total_members; i++)
			{
				if (m_members[i]->getName() == c) // if finds name
				{
					delete m_members[i]; // delete object from array
					idx_deleted = i; // saves index for next loop
					i = m_total_members; // exit loop
				}
			}

			for (int i = 0, j = 0; i < m_total_members; i++)
			{
				if (idx_deleted != i) // make sure we dont iteract with deleted index
					tmp_array[j++] = m_members[i]->clone(); // assign each character
			}
			delete[] m_members; // delete whole array

			m_members = tmp_array; // points to new updated array address 

			m_total_members--; // update member counter
		}
	}

	// make sure index is a valid number
	Character* Team::operator[](size_t idx) const { return (int)idx >= m_total_members ? nullptr : m_members[idx]; }

	// display all members from team individually
	void Team::showMembers() const
	{
		if (m_total_members != 0) // make sure members array is not empty
		{
			std::cout << "[Team] " << this->getTeamName() << std::endl; // displays team name
			for (int i = 0; i < m_total_members; i++)
			{
				std::cout << "    " << i + 1 << ": " << *m_members[i] << std::endl; // display member individually
			}
		}
		else 
		{
			std::cout << "No team." << std::endl; // if total members are 0, display no member message
		}
	}

	// destructor
	Team::~Team()
	{
		if (m_members != nullptr) { // make sure we dont iteract trough a null pointer
			for (int i = 0; i < m_total_members; i++)
			{
				if (m_members[i])
				delete m_members[i]; // delete each pointer individually
			}
			delete[] m_members; // delete whole array
			m_members = nullptr; // set to a safe empty state
		}
	}

}