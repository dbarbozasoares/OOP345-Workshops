#include "shoppingCart.h"

namespace seneca {
    std::ostream& operator<<(std::ostream& ostr, const ShoppingCart& cart)
    {
        static int CALL_CNT = 0;
        ++CALL_CNT;

        if (cart.m_toys == nullptr || cart.m_toy_count == 0)
        {
            ostr << "Shopping cart is empty.\n";
        }
        else if (cart.m_toys[0]->getId() == 0)
        {
            ostr << "No toys available in the cart.\n";
        }
        else
        {
            ostr << "Child Name: " << cart.childName() << "\n";
            ostr << "Child Age: " << cart.childAge() << "\n";
            ostr << "Toy Count: " << cart.toyCount() << "\n";
            ostr << "Toys:\n";
            for (size_t i = 0; i < cart.toyCount(); ++i)
            {
                ostr << "  - Toy " << i + 1 << ": " << *cart.m_toys[i] << "\n";
            }
        }

        return ostr;
    }

	ShoppingCart::ShoppingCart() : m_toys(nullptr), m_child_age(0), m_child_name(""), m_toy_count(0) {}

    std::string ShoppingCart::childName() const { return m_child_name; }

    int ShoppingCart::childAge() const { return m_child_age; }

    int ShoppingCart::toyCount() const { return m_toy_count; }

	ShoppingCart::ShoppingCart(const std::string& name, int age, const Toy* toys[], size_t count) : m_child_name(name), m_child_age(age), m_toy_count(count)
	{	
		for (size_t i = 0; i < count; i++)
		{
			m_toys[i] = toys[i];
		}
	}
}