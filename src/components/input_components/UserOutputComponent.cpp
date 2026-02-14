/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** UserOutputComponent
*/

#include "UserOutputComponent.hpp"
#include "Circuit.hpp"
#include "IComponent.hpp"


nts::UserOutputComponent::UserOutputComponent()
{
    component_links = {{1, InputType}};
}

void nts::UserOutputComponent::simulate(size_t tick)
{
    compute(1);
}

nts :: Tristate nts::UserOutputComponent::compute(size_t pin)
{
    real_value = getLink(1);
    display_value = real_value;
    return display_value;
}
