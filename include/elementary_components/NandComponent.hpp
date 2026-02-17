/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** NandComponent
*/

#ifndef INCLUDED_NANDCOMPONENT_HPP
    #define INCLUDED_NANDCOMPONENT_HPP

#include <iostream>

#include "AComponent.hpp"
#include "IComponent.hpp"

namespace nts {


class NandComponent : public virtual AComponent
{
    private:
    protected:
    public:
        NandComponent();
        nts :: Tristate compute ( std :: size_t pin ) override;

};
}

#endif
