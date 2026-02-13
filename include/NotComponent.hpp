/*
** EPITECH PROJECT, 2026
** bootstrap_nanotekspice
** File description:
** NotComponent
*/

#ifndef INCLUDED_NOTCOMPONENT_HPP
    #define INCLUDED_NOTCOMPONENT_HPP

#include "AComponent.hpp"
#include "IComponent.hpp"

namespace nts {

class NotComponent : public virtual AComponent
{
    private:
    protected:
    public:
        NotComponent();
        //~NotComponent() = default;

        nts :: Tristate compute ( std :: size_t pin ) override;

};

}
#endif
