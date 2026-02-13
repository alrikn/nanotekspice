/*
** EPITECH PROJECT, 2026
** bootstrap_nanotekspice
** File description:
** FalseComponent
*/

#ifndef INCLUDED_FALSECOMPONENT_HPP
    #define INCLUDED_FALSECOMPONENT_HPP

#include "AComponent.hpp"
#include "IComponent.hpp"


namespace nts {

class FalseComponent  : public virtual AComponent
{
    private:
    protected:
    public:
        //FalseComponent();
        //~FalseComponent() = default;

        FalseComponent();
        nts :: Tristate compute ( std :: size_t pin ) override;

};

}
#endif
