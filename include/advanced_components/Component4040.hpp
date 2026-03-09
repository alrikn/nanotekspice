/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Component4040
*/

#ifndef INCLUDED_COMPONENT4040_HPP
    #define INCLUDED_COMPONENT4040_HPP

#include "AComponent.hpp"
#include <cstddef>

namespace nts {



class Component4040 : public virtual AComponent
{
    private:
        size_t counter = 0;
        nts::Tristate last_clock = nts::Tristate::False;
    protected:
    public:
        Component4040();
        void simulate(size_t tick) override; //we need to overwrite simulate since we need to update the flipflops even if they aren't called by another component, since they need to update themselves on the rising edge of the clock
        nts :: Tristate compute ( std :: size_t pin ) override;

};
}
#endif
