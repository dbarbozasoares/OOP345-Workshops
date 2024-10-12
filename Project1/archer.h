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
#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H

#include "characterTpl.h"
#include "health.h"
#include <iostream>  // for outputting attack details

namespace seneca {

	template <class Weapon_t>
	class Archer : public CharacterTpl<seneca::SuperHealth> {
		int m_baseAttack; // base attaack
		int m_baseDefense; // base deffense
		Weapon_t m_weapon; // Only one weapon
	public:
		Archer(); // default constructor
		Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon); // parametized constructor
		int getAttackAmnt() const override; // return attack with weapon bonus
		int getDefenseAmnt() const override; // return base deffense
		Character* clone() const override; // return a reference copy from current object
		void attack(Character* enemy); // attack an enemy
		void takeDamage(int dmg); // receives a damage
	};

	// Default constructor
	template<class Weapon_t>
	Archer<Weapon_t>::Archer() : m_baseAttack(0), m_baseDefense(0), m_weapon({}) {}

	// Parameterized constructor
	template<class Weapon_t>
	Archer<Weapon_t>::Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon)
		: CharacterTpl<seneca::SuperHealth>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense), m_weapon(weapon) 
	{
		this->setHealth(healthMax);
	}

	// Attack amount with bonus
	template<class Weapon_t>
	int Archer<Weapon_t>::getAttackAmnt() const { return (1.3 * m_baseAttack); }

	// Defense amount with bonus
	template<class Weapon_t>
	int Archer<Weapon_t>::getDefenseAmnt() const { return (1.2 * m_baseDefense); }

	// Clone method returning copy reference from current object
	template<class Weapon_t>
	Character* Archer<Weapon_t>::clone() const {
		return new Archer<Weapon_t>(*this);
	}

	// Attack an enemy method
	template<class Weapon_t>
	void Archer<Weapon_t>::attack(Character* enemy) {
		std::cout << Character::getName() << " is attacking " << enemy->getName() << "." << std::endl;
		std::cout << "Archer deals " << getAttackAmnt() << " ranged damage!" << std::endl;
		enemy->takeDamage(getAttackAmnt());
	}

	// Take damage method (calls base class)
	template<class Weapon_t>
	void Archer<Weapon_t>::takeDamage(int dmg) {
		std::cout << Character::getName() << " is attacked for " << dmg << " damage." << std::endl;
		std::cout << "   Archer has a defense of " << getDefenseAmnt() << ". Reducing damage received." << std::endl;
		int reducedDmg = dmg - getDefenseAmnt();
		if (reducedDmg > 0)
			CharacterTpl<seneca::SuperHealth>::takeDamage(reducedDmg);
	}

}

#endif // SENECA_ARCHER_H
