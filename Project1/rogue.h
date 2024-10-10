#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H

#include "characterTpl.h"
#include "weapons.h"
#include "abilities.h"

namespace seneca {

	// T refers to base class m_health type
	template <class T, class FirstAbility_t, class SecondAbility_t>
	class Rogue : public CharacterTpl<T> {
		int m_baseAttack; // base attack
		int m_baseDefense; // base defense
		FirstAbility_t m_firstAbility; // first special ability
		SecondAbility_t m_secondAbility; // second special ability
		Dagger m_weapon; // rogue's weapon (dagger)
	public:
		Rogue();
		Rogue(const char* name, int healthMax, int baseAttack, int baseDefense); // parameterized constructor
		int getAttackAmnt() const; // returns attack amount with weapon bonus
		int getDefenseAmnt() const; // returns base defense amount
		Character* clone() const; // return a reference copy from current object
		void attack(Character* enemy); // attack an enemy
		void takeDamage(int dmg); // receives damage
	};

	// +++++++++++++++++++++++++++
	// Method implementations
	// +++++++++++++++++++++++++++

	template<class T, class FirstAbility_t, class SecondAbility_t>
	Rogue<T, FirstAbility_t, SecondAbility_t>::Rogue() : m_baseAttack(0), m_baseDefense(0), m_firstAbility(), m_secondAbility(), m_weapon() {}

	// Parameterized constructor
	template<class T, class FirstAbility_t, class SecondAbility_t>
	Rogue<T, FirstAbility_t, SecondAbility_t>::Rogue(const char* name, int healthMax, int baseAttack, int baseDefense)
		: CharacterTpl<T>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense) {
		this->setHealth(healthMax);
	}

	// Return attack amount with weapon bonus
	template<class T, class FirstAbility_t, class SecondAbility_t>
	int Rogue<T, FirstAbility_t, SecondAbility_t>::getAttackAmnt() const {
		return (m_baseAttack + (2 * m_weapon.m_damage));
	}

	// Return base defense amount
	template<class T, class FirstAbility_t, class SecondAbility_t>
	int Rogue<T, FirstAbility_t, SecondAbility_t>::getDefenseAmnt() const {
		return m_baseDefense;
	}

	// Clone method returning a copy reference from the current object
	template<class T, class FirstAbility_t, class SecondAbility_t>
	Character* Rogue<T, FirstAbility_t, SecondAbility_t>::clone() const {
		return new Rogue<T, FirstAbility_t, SecondAbility_t>(*this);
	}

	// Attack an enemy method
	template<class T, class FirstAbility_t, class SecondAbility_t>
	void Rogue<T, FirstAbility_t, SecondAbility_t>::attack(Character* enemy) {
		int enhanced_attack = getAttackAmnt();
		std::cout << Character::getName() << " is attacking " << enemy->getName() << "." << std::endl;
		m_firstAbility.useAbility(this);
		m_secondAbility.useAbility(this);

		m_firstAbility.transformDamageDealt(enhanced_attack);
		m_secondAbility.transformDamageDealt(enhanced_attack);

		std::cout << "Rogue deals " << enhanced_attack << " melee damage!" << std::endl;

		enemy->takeDamage(enhanced_attack);
	}

	// Take damage method (calls base class)
	template<class T, class FirstAbility_t, class SecondAbility_t>
	void Rogue<T, FirstAbility_t, SecondAbility_t>::takeDamage(int dmg) {
		int dmg_received = getDefenseAmnt() - dmg;
		std::cout << Character::getName() << " is attacked for " << dmg << " damage." << std::endl;
		std::cout << "   Rogue has a defense of " << getDefenseAmnt() << ". Reducing damage received." << std::endl;

		if (dmg_received > 0) {
			m_firstAbility.transformDamageReceived(dmg_received);
			m_secondAbility.transformDamageReceived(dmg_received);
			CharacterTpl<T>::takeDamage(dmg_received);
		}
	}

}

#endif // !SENECA_ROGUE_H
