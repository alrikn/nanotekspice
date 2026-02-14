/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** UserOutputComponent
*/

#ifndef INCLUDED_USEROUTPUTCOMPONENT_HPP
    #define INCLUDED_USEROUTPUTCOMPONENT_HPP

#include "ASpecialComponent.hpp"
#include "IComponent.hpp"


namespace nts {

class UserOutputComponent  : public virtual ASpecialComponent
{
    private:
    protected:
    public:
        //UserOutputComponent();
        //~UserOutputComponent() = default;
        void simulate(size_t tick) override;
        UserOutputComponent();
        nts :: Tristate compute ( std :: size_t pin ) override;

};
}
#endif
