/*
** EPITECH PROJECT, 2026
** bootstrap_nanotekspice
** File description:
** Circuit
*/

#ifndef INCLUDED_CIRCUIT_HPP
    #define INCLUDED_CIRCUIT_HPP

#include <csignal>
#include <memory>
#include "IComponent.hpp"
#include <map>


namespace nts {

enum PinType { //primes (cus if u add up any with each other or with itself its a unique val)
    InputType = 1, //can only be connected to a single output
    OuputType = 3, //can only be connect to one or more input
    LogOutputType = 5, //this is a special case and needs to be handled carefully
    UndefinedType = 7
};

const std::initializer_list<int> pin_combinations = { //there is probably a better way but it is late and i am tired
    OuputType + InputType, //normal input + normal output
};

enum ClassType {
    NormalComponent,
    LoggerComponent, //this is useful to keep because this is special case, and we need to call comput on it directly (overwrite simultate)
    ClockComponent, //i am not sure this one has good reason to be here? we might need to remove it.
    InDisplayComponent, //what we show on the display, no special treatement needed
    OutDisplayComponent, //what we show on the display, it needs special tretement, (class needs to overwrite simulate)
};

struct ComponentEntry {
    std::unique_ptr<IComponent> component;
    ClassType type;
};

class Circuit {
    private:
        std::map<std::string, ComponentEntry> components;
    public:
        Circuit() = default;
        ~Circuit() = default;
        void addComponent(std::string name, std::unique_ptr<IComponent> c, ClassType type);
        std::unique_ptr<IComponent> &getComponent(std::string const &name);

        void simulate(std::size_t tick);

        ClassType getType(const std::string& name);


        void display();

};
}

#endif
