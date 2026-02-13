/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** ASpecialComponent
*/

#ifndef INCLUDED_ASPECIALCOMPONENT_HPP
    #define INCLUDED_ASPECIALCOMPONENT_HPP

#include "AComponent.hpp"
#include "IComponent.hpp"
#include <iostream>

namespace nts {



class ASpecialComponent : public virtual AComponent
{
    private:
    protected:
        Tristate display_value = Undefined; //display value only gets updated when compute gets called on it
        Tristate real_value; //this is the one that is always up to date
    public:
        Tristate get_display_value() {return display_value;}
        void set_real_value(Tristate new_value) {real_value = new_value;}
};
}


#endif
