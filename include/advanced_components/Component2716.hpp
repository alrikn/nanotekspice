/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Component2716
*/

#ifndef INCLUDED_COMPONENT4801_HPP
    #define INCLUDED_COMPONENT4801_HPP

#include "AComponent.hpp"
#include "IComponent.hpp"
#include <bitset>

namespace nts {


class Component2716 : public virtual AComponent
{
    private:
        char _memory[2048 *8] = {false}; //2048 bytes of memory, each byte has 8 bits
        //every bool takes 1 bytes but there should be a way to make it take one bit per bool.
    protected:
    public:
        Component2716();
        nts :: Tristate compute ( std :: size_t pin ) override;

};
}
#endif
