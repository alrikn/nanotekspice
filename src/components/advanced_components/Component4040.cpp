/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Component4040
*/

#include "Component4040.hpp"
#include "IComponent.hpp"
#include <cstdio>

#include "Component4040.hpp"
#include "IComponent.hpp"

using namespace nts;

Component4040::Component4040()
{
    component_links = {
        {1, OutputType},  // Q11
        {2, OutputType},  // Q5
        {3, OutputType},  // Q4
        {4, OutputType},  // Q6
        {5, OutputType},  // Q3
        {6, OutputType},  // Q2
        {7, OutputType},  // Q1
        {8, UndefinedType},
        {9, OutputType},  // Q0
        {10, InputType},  // CLOCK
        {11, InputType},  // RESET
        {12, OutputType}, // Q8
        {13, OutputType}, // Q7
        {14, OutputType}, // Q9
        {15, OutputType}, // Q10
        {16, UndefinedType}
    };
}

void Component4040::simulate(size_t tick)
{
    Tristate reset = getLink(11);
    Tristate clock = getLink(10);

    if (reset == True) {
        _counter = 0;
        _lastClock = clock;
        return;
    }

    bool rising = (_lastClock == False && clock == True);

    if (rising)
        _counter = (_counter + 1) & 0x0FFF; // 12 bits

    _lastClock = clock;
}

Tristate Component4040::compute(size_t pin)
{
    switch (pin) {
        case 9:  return ((_counter >> 0) & 1) ? True : False;
        case 7:  return ((_counter >> 1) & 1) ? True : False;
        case 6:  return ((_counter >> 2) & 1) ? True : False;
        case 5:  return ((_counter >> 3) & 1) ? True : False;
        case 3:  return ((_counter >> 4) & 1) ? True : False;
        case 2:  return ((_counter >> 5) & 1) ? True : False;
        case 4:  return ((_counter >> 6) & 1) ? True : False;
        case 13: return ((_counter >> 7) & 1) ? True : False;
        case 12: return ((_counter >> 8) & 1) ? True : False;
        case 14: return ((_counter >> 9) & 1) ? True : False;
        case 15: return ((_counter >> 10) & 1) ? True : False;
        case 1:  return ((_counter >> 11) & 1) ? True : False;

        case 10: return getLink(10);
        case 11: return getLink(11);
    }
    return Undefined;
}
