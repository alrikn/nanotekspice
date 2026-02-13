/*
** EPITECH PROJECT, 2026
** bootstrap_nanotekspice
** File description:
** AndComponent
*/

#ifndef INCLUDED_ANDCOMPONENT_HPP
    #define INCLUDED_ANDCOMPONENT_HPP

#include "AComponent.hpp"
#include "IComponent.hpp"

namespace nts {


class AndComponent : public virtual AComponent
{
    private:
    protected:
    public:
        AndComponent();
        nts :: Tristate compute ( std :: size_t pin ) override;

};
}

#endif
