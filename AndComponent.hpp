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
#include <iostream>

namespace nts {


class AndComponent : public virtual AComponent
{
    private:
    protected:
    public:

        nts :: Tristate compute ( std :: size_t pin ) override
        {
            if (pin != 2) //the return pin
                return Undefined;
            auto a = getLink(0);
            auto b = getLink(1);

            //most scuffed way of doing and statement, but can't think of anything better
            if (a == Undefined || b == Undefined)
                return Undefined;
            if (a == False || b == False)
                return False;
            return True;
        }

};
}

#endif
