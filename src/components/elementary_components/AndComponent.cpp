/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** AndComponent
*/

#include "AndComponent.hpp"
#include "Circuit.hpp"

nts::AndComponent::AndComponent()
{
    component_links = {
        {1, InputType},
        {2, InputType},
        {3, OuputType},
    };
}

nts :: Tristate nts::AndComponent::compute ( std :: size_t pin )
{
    if (pin != 3) //the return pin
        return Undefined;
    auto a = getLink(1);
    auto b = getLink(2);
    
    //most scuffed way of doing and statement, but can't think of anything better
    if (a == Undefined || b == Undefined)
        return Undefined;
    if (a == False || b == False)
        return False;
    return True;
}
