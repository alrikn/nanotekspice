/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** AGateComponent
*/

#ifndef INCLUDED_AGATECOMPONENT_HPP
    #define INCLUDED_AGATECOMPONENT_HPP

#include "AComponent.hpp"
#include "IComponent.hpp"
#include <functional>
#include <iostream>
#include <map>
#include <vector>
namespace nts {


struct GateInfo {
    std::vector<int> InputPins;//external input pins (ex: {1,2} for a 2 input gate)
    int GateOutputPin;//external output pin (the default otput pins for gatees are 3 4 11 and 10)
    int OutputPin;//internal output pin of the elementary gate (usually 3 for 2 input, 2 for inverter)
};

class AGateComponent : public virtual AComponent
{
    private:
        struct GateHolder {
            std::unique_ptr<AComponent> comp; //thats the elementary comp
            int subOutputPin;
        };
        std::vector<GateHolder> m_gates; //mmmm gates, (list of elementarty gates with output pins)
        std::unordered_map<int, std::size_t> m_outputToGate;
    //protected:pññ-....................................................................................................................................................................................... so said my cat
    public:
        AGateComponent(const std::vector<GateInfo>& gateInfos, //mmmm links...
                   std::function<std::unique_ptr<AComponent>()> factory, //I love function pointers
                   int maxPin = 14);
        virtual ~AGateComponent() = default;
        nts::Tristate compute(std::size_t pin) override;
};//
}

#endif
