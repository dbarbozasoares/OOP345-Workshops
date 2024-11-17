#ifndef SENECA_SHOPPING_CART_H
#define SENECA_SHOPPING_CART_H
#include "toy.h"

namespace seneca {
	class ShoppingCart {
		const Toy** m_toys;
		std::string m_child_name;
		int m_child_age;
		int m_toy_count;
	public:
		ShoppingCart();
		std::string childName() const;
		int childAge() const;
		int toyCount() const;
		ShoppingCart(const std::string& name, int age, const Toy* toys[], size_t count);

		friend std::ostream& operator<<(std::ostream& ostr, const ShoppingCart&);
	};
}

#endif // !SENECA_SHOPPING_CART_H
