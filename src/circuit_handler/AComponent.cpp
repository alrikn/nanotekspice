/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** AComponent
*/

#include "AComponent.hpp"
#include "Circuit.hpp"
#include "HashMapCache.hpp"
#include <cstddef>


void nts::AComponent::simulate(size_t tick)
{
    return;
}

//set da link
void nts::AComponent::setLink(size_t pin, nts::IComponent &other, size_t otherPin)
{
    //TODO: you should be able to connect may pins to a single output, but only to outputs
    //so figure that out
    _links[pin] = {&other, otherPin};
}

nts::Tristate nts::AComponent::getLink(size_t pin)
{
    if (_links.count(pin) == 0)
        return Undefined;
    auto &da_link = _links[pin];
    return compute_hashmap(da_link.component, da_link.pin); //compute takes as an input the supposed return pin
}

nts::Class_type nts::AComponent::get_type(size_t pin)
{
    if (component_links.count(pin) == 0)
        return UndefinedType;
    return component_links[pin];
}