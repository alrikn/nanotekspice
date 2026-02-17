/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Component4069
*/

#include "Component4069.hpp"
#include "AGateComponent.hpp"
#include "NotComponent.hpp"

std::unique_ptr<nts::NotComponent> make_func()
{
    return std::make_unique<nts::NotComponent>();
}

nts::Component4069::Component4069() : nts::AGateComponent({
                    {{1},  2, 2},
                    {{3},  4, 2},
                    {{5},  6, 2},
                    {{9},  8, 2},
                    {{11}, 10, 2},
                    {{13}, 12, 2}
                },
                make_func
            )
{
    //i could put this entire thing in hpp but then it would be inconsistent
}