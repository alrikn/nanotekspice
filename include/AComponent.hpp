/*
** EPITECH PROJECT, 2026
** bootstrap_nanotekspice
** File description:
** AComponent
*/

#ifndef INCLUDED_ACOMPONENT_HPP
    #define INCLUDED_ACOMPONENT_HPP

#include "Circuit.hpp"
#include "IComponent.hpp"
#include <cstddef>
#include <map>
namespace nts {
class AComponent : public virtual IComponent
{
    private:
    protected:
        struct Link { //were gunna make a list of which links are connected where
            nts::IComponent *component = nullptr; //which component are we talking about
            size_t pin = 0; //other pin
        };

        //index of map is gonna be our pin, and holds other pin as well as ref to other component
        std::map<size_t, Link> _links; //just make a map of links

        std::map<size_t, Class_type> component_links = {{1, UndefinedType}};

    public:
        AComponent() = default;
        //AComponent(const AComponent& other);
        //AComponent& operator=(const AComponent& other);
        ~AComponent() = default;

        //void display(ostream& os = cout);
        void simulate(size_t tick) override;

        //set da link
        void setLink(size_t pin, nts::IComponent &other, size_t otherPin) override;

        nts::Tristate getLink(size_t pin);

        Class_type get_type(size_t pin); //gets the pin from the component link
};
}

#endif
