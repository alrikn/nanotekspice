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
        AndComponent();

        //ngl i have genuinely no clue what compute takes as an input.
        //i have 0 clue what pin its supposed to be. is it the output pin?
        //shouldn't we already have all our inputs?
        //what is going on
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
