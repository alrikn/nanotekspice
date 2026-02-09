/*
** EPITECH PROJECT, 2026
** bootstrap_nanotekspice
** File description:
** NotComponent
*/

#ifndef INCLUDED_NOTCOMPONENT_HPP
    #define INCLUDED_NOTCOMPONENT_HPP

#include <iostream>
#include "AComponent.hpp"
#include "IComponent.hpp"

namespace nts {

class NotComponent : public virtual AComponent
{
    private:
    protected:
    public:
        //NotComponent();
        //~NotComponent() = default;

        nts :: Tristate compute ( std :: size_t pin ) override
        {
            if (pin != 1) //return pin
                return Undefined;

            auto input = getLink(0);

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

};

}
#endif
