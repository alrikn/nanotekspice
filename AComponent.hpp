/*
** EPITECH PROJECT, 2026
** bootstrap_nanotekspice
** File description:
** AComponent
*/

#ifndef INCLUDED_ACOMPONENT_HPP
    #define INCLUDED_ACOMPONENT_HPP

#include "IComponent.hpp"
#include <cstdint>
#include <iostream>
#include <map>
namespace nts {
class AComponent : public virtual IComponent
{
    private:
    protected:
        struct Link { //were gunna make a list of which links are connected where
            nts::IComponent *component = nullptr; //which component are we talking about
            std::size_t pin = 0; //other pin
        };

        //index of map is gonna be our pin, and holds other pin as well as ref to other component
        std::map<std::size_t, Link> _links; //just make a map of links

    public:
        AComponent() = default;
        //AComponent(const AComponent& other);
        //AComponent& operator=(const AComponent& other);
        ~AComponent() = default;

        //void display(std::ostream& os = std::cout);
        void simulate(std::size_t tick) override
        {
            return;
        }

        //set da link
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override
        {
            _links[pin] = {&other, otherPin};
        }

        nts::Tristate getLink(std::size_t pin)
        {
            if (_links.count(pin) == 0)
                return Undefined;
            return _links[pin].component->compute(_links[pin].pin); //compute takes as an input the supposed return pin
        }
};
}
std::ostream& operator<<(std::ostream& os, const nts::AComponent& obj);

#endif
