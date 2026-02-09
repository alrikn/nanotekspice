/*
** EPITECH PROJECT, 2026
** bootstrap_nanotekspice
** File description:
** AComponent
*/

#ifndef INCLUDED_ACOMPONENT_HPP
    #define INCLUDED_ACOMPONENT_HPP

#include "IComponent.hpp"
#include <iostream>
namespace nts {
class AComponent : virtual IComponent
{
    private:
    protected:
    public:
        AComponent();
        AComponent(const AComponent& other);
        AComponent& operator=(const AComponent& other);
        ~AComponent() = default;

        void display(std::ostream& os = std::cout);
};
}
std::ostream& operator<<(std::ostream& os, const nts::AComponent& obj);

#endif
