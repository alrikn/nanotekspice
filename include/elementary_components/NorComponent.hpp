/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** NorComponent
*/

#ifndef INCLUDED_NORCOMPONENT_HPP
    #define INCLUDED_NORCOMPONENT_HPP

#include "AComponent.hpp"

namespace nts {



class NorComponent : public virtual AComponent
{
    private:
    protected:
    public:
        NorComponent();
        nts :: Tristate compute ( std :: size_t pin ) override;

};
}
#endif
