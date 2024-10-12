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
#ifndef SENECA_CHARACTER_TPL_H
#define SENECA_CHARACTER_TPL_H

#include "character.h"
#include <iostream>

namespace seneca {

    template <class T>
    class CharacterTpl : public Character {
        int m_healthMax;  // Maximum health of the character
        T m_health;       // Current health type of the character
    public:
        CharacterTpl(const char* name, int maxHealth);  // Parameterized constructor
        operator int() const;  // Conversion operator type T to int
        CharacterTpl<T>& operator-=(int damage);  // Damage operator overload
        int getHealth() const override;  // Get current health converted to int
        void takeDamage(int dmg) override;  // Apply damage to the character
        int getHealthMax() const override;  // Get maximum health
        void setHealth(int health) override;  // Set current health
        void setHealthMax(int health) override;  // Set maximum health
    };

    // Parameterized constructor
    template<class T>
    CharacterTpl<T>::CharacterTpl(const char* name, int healthMax) : Character(name), m_healthMax(healthMax) {
        setHealth(healthMax);
    }

    // Conversion operator to int
    template<class T>
    CharacterTpl<T>::operator int() const {
        return static_cast<int>(m_health);
    }

    // Damage operator overload
    template<class T>
    CharacterTpl<T>& CharacterTpl<T>::operator-=(int damage) {
        m_health -= damage;
        return *this;
    }

    // Get current health
    template<class T>
    int CharacterTpl<T>::getHealth() const {
        return static_cast<int>(m_health);
    }

    // Get maximum health
    template<class T>
    int CharacterTpl<T>::getHealthMax() const {
        return this->m_healthMax;
    }

    // Set current health
    template<class T>
    void CharacterTpl<T>::setHealth(int health) {
        if (health >= 0) {
            m_health = health;
        }
    }


    // Set maximum health
    template<class T>
    void CharacterTpl<T>::setHealthMax(int health) {
        if (health > 0) {
            m_healthMax = health;
        }
    }

    // Apply damage to the character
    template<class T>
    void CharacterTpl<T>::takeDamage(int dmg) {
        if (dmg > 0) {
            m_health -= dmg;
        }
        if (!isAlive() || getHealth() <= 0) {
            std::cout << "    " << getName() << " has been defeated!" << std::endl;
            this->setHealth(0);
        }
        else {
            std::cout << "    " << getName() << " took " << dmg << " damage, "
                << getHealth() << " health remaining." << std::endl;
        }
    }

} // namespace seneca

#endif // SENECA_CHARACTER_TPL_H
