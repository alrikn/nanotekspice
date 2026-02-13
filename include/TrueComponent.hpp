/*
** EPITECH PROJECT, 2026
** bootstrap_nanotekspice
** File description:
** TrueComponent
*/

#ifndef INCLUDED_TRUECOMPONENT_HPP
    #define INCLUDED_TRUECOMPONENT_HPP


#include "AComponent.hpp"
#include "IComponent.hpp"

namespace nts {

class TrueComponent  : public virtual AComponent
{
    private:
    protected:
    public:
        TrueComponent();
        //~TrueComponent() = default;

        nts :: Tristate compute ( std :: size_t pin ) override;

};

}
#endif
