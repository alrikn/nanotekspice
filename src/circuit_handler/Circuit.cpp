/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Circuit
*/

#include "Circuit.hpp"
#include "ASpecialComponent.hpp"
#include "HashMapCache.hpp"

namespace nts {



void Circuit::addComponent(std::string name, std::unique_ptr<IComponent> c, ClassType type)
{
    if (components.count(name) >= 1)
        throw std::runtime_error("Component already exists");
    components[name] = {std::move(c), type}; //uniqueptr can only be moved not copied
}

std::unique_ptr<IComponent> &Circuit::getComponent(std::string const &name)
{
    if (components.count(name) == 0)
        raise(3); //placeholder until we find real error
    return components[name].component;
}

void Circuit::simulate(std::size_t tick) { // there should probably be an order of execution
    g_current_tick = tick;
    //we only need to pay attention to the logger and execute it directly,
    // since it has an output valve that goes outside of the program in a sense
    // (that or the logger needs to overwrite the simulate which works too)
    for (auto &c : components)
        c.second.component->simulate(tick);
}

ClassType Circuit::getType(const std::string& name)
{
    return components.at(name).type;
}

std :: ostream & operator <<( std :: ostream & s , nts :: Tristate v)
{
    if (v == nts::Undefined)
        s << "U";
    if (v == nts::True)
        s << "1";
    if (v == nts::False)
        s << "0";
    return s;
}

void Circuit::display()
{
    std::cout << "Display Input:" << std::endl;
    //the component are stored as IComponents (grandfather class that is virtual)
    for (auto &c : components)
        if (c.second.type == InDisplayComponent) { //i know a 100% that this is an ASpecialComponent type class
            auto* special = dynamic_cast<ASpecialComponent*>(c.second.component.get());

            if (special)
                std::cout << c.first << " = " << special->get_display_value() << std::endl;

        }

    std::cout << "Display Output:" << std::endl;
    for (auto &c : components)
        if (c.second.type == OutDisplayComponent) { //i know a 100% that this is an ASpecialComponent type class
            auto* special = dynamic_cast<ASpecialComponent*>(c.second.component.get());

            if (special)
                std::cout << c.first << " = " << special->get_display_value() << std::endl;

        }
    
    std::cout << "End of display command \n" << std::endl;
}

}
