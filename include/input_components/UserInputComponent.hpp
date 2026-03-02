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
        void simulate(size_t tick) override;
        Tristate get_display_value() override {return real_value;} //possible reason why thhe mouli shows undefined when it supposed to be set
        UserInputComponent();
        nts :: Tristate compute ( std :: size_t pin ) override;

};
}
#endif
