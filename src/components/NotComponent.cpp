/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** NotComponent
*/

#include "NotComponent.hpp"


nts::NotComponent::NotComponent()
{
    component_links = {
        {1, InputType},
        {2, OuputType},
    };
}

nts :: Tristate nts::NotComponent::compute ( std :: size_t pin )
{
    if (pin != 2) //return pin
        return Undefined;
    auto input = getLink(1);

    switch (input) {
        case Undefined:
            return Undefined;
        case True:
            return False;
        case False:
            return True;
    }
    return Undefined;
}

