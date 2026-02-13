/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** UserInputComponent
*/

#ifndef INCLUDED_USERINPUTCOMPONENT_HPP
    #define INCLUDED_USERINPUTCOMPONENT_HPP

#include "AComponent.hpp"
#include "ASpecialComponent.hpp"
#include "IComponent.hpp"


namespace nts {

class UserInputComponent  : public virtual ASpecialComponent
{
    private:
    protected:
    public:
        //UserInputComponent();
        //~UserInputComponent() = default;

        UserInputComponent();
        nts :: Tristate compute ( std :: size_t pin ) override;

};
}
#endif
