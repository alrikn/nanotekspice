/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** UserInputComponent
*/


#include "UserInputComponent.hpp"
#include "Circuit.hpp"
#include "IComponent.hpp"


nts::UserInputComponent::UserInputComponent()
{
    component_links = {{1, OuputType}};
}

nts :: Tristate nts::UserInputComponent::compute(size_t pin)
{
    display_value = real_value;
    if (pin == 1)
        return real_value;
    return Undefined;
}
