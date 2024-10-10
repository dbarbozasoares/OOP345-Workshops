#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H
#include "characterTpl.h"
#include "weapons.h"
#define BARBARIAN_TOTAL_WEAPONS 2

namespace seneca {

    template <class T, class Ability_t, class Weapon_t>
    class Barbarian : public CharacterTpl<T> {
        T m_max_health; // max health a barbarian can have
        int m_baseAttack;// base attack
        int m_baseDefense; // base deffense
        Ability_t m_ability; // ability that a barbarian holds
        Weapon_t m_weapon[BARBARIAN_TOTAL_WEAPONS]; // array for weapons for barbarian

    public:
        Barbarian();
        Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon);
        int getAttackAmnt() const; // return base attack with weapon bonus
        int getDefenseAmnt() const; // return base deffense
        Character* clone() const; // return a copy reference from current object
        void attack(Character* enemy); // attack an enemy
        void takeDamage(int dmg); // receive some damage reduced by ability
    };

    // Implementations

    template<class T, class Ability_t, class Weapon_t>
    Barbarian<T, Ability_t, Weapon_t>::Barbarian() : m_baseAttack(0), m_baseDefense(0), m_ability({}), m_weapon({}) {}

    template <class T, class Ability_t, class Weapon_t>
    Barbarian<T, Ability_t, Weapon_t>::Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon)
        : CharacterTpl<T>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense), m_ability(Ability_t()) {
        m_weapon[0] = primaryWeapon;
        m_weapon[1] = secondaryWeapon;
        this->setHealth(healthMax);
    }

    template <class T, class Ability_t, class Weapon_t>
    int Barbarian<T, Ability_t, Weapon_t>::getAttackAmnt() const {
        return (m_baseAttack + (m_weapon[0].m_damage / 2) + (m_weapon[1].m_damage / 2));
    }

    template <class T, class Ability_t, class Weapon_t>
    int Barbarian<T, Ability_t, Weapon_t>::getDefenseAmnt() const {
        return m_baseDefense;
    }

    template <class T, class Ability_t, class Weapon_t>
    Character* Barbarian<T, Ability_t, Weapon_t>::clone() const {
       return new Barbarian<T, Ability_t, Weapon_t>(*this);
    }

    template <class T, class Ability_t, class Weapon_t>
    void Barbarian<T, Ability_t, Weapon_t>::attack(Character* enemy) {
        std::cout << Character::getName() << " is attacking " << enemy->getName() << "." << std::endl;
        m_ability.useAbility(this);

        int enhanced_damage = getAttackAmnt();
        m_ability.transformDamageDealt(enhanced_damage);

        std::cout << "    Barbarian deals " << enhanced_damage << " melee damage!" << std::endl;
        enemy->takeDamage(enhanced_damage);
    }

    template <class T, class Ability_t, class Weapon_t>
    void Barbarian<T, Ability_t, Weapon_t>::takeDamage(int dmg) {
        int damage_taken = dmg - getDefenseAmnt();

        std::cout << Character::getName() << " is attacked for " << dmg << " damage." << std::endl;
        std::cout << "    Barbarian has a defense of " << getDefenseAmnt() << ". Reducing damage received." << std::endl;

        if (dmg > 0 && damage_taken > 0) {
            m_ability.transformDamageReceived(damage_taken);
            CharacterTpl<T>::takeDamage(damage_taken);
        }
    }
}
#endif // SENECA_BARBARIAN_H
