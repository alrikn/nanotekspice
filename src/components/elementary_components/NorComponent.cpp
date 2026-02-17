/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** NorComponent
*/

#include "NorComponent.hpp"
#include "Circuit.hpp"

nts::NorComponent::NorComponent()
{
    component_links = {
        {1, InputType},
        {2, InputType},
        {3, OuputType},
    };
}

nts :: Tristate nts::NorComponent::compute ( std :: size_t pin )
{
    if (pin != 3) //the return pin
        return Undefined;
    auto a = getLink(1);
    auto b = getLink(2);

    if (a == Undefined || b == Undefined)
        return Undefined;
    if (a == False && b == False)
        return True;
    return False;
}
