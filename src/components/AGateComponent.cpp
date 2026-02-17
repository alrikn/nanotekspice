/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** AGateComponent
*/

#include "AGateComponent.hpp"
#include <unordered_set>

nts::AGateComponent::AGateComponent(const std::vector<GateInfo>& gateInfos,
                                     std::function<std::unique_ptr<AComponent>()> factory,
                                     int maxPin)
{
    //temporary sets to collect all external input and output pins from the gateInfos.
    //we'll use these to build the component_links map (pin type: input, output, undefined). (this won't work for logger, but loggers not a gate though)
    std::unordered_set<int> inputPins;
    std::unordered_set<int> outputPins;

    //each gate desc
    for (const auto& info : gateInfos) {
        //all gate input pins (of the gate so external pins technically) are added to input set
        for (int in : info.InputPins)
            inputPins.insert(in);
        //same for output pin (only one per gate thingy)
        outputPins.insert(info.GateOutputPin);
    }

    //we assign type to everything in component links
    for (int pin = 1; pin <= maxPin; pin++) {
        if (inputPins.count(pin))
            component_links[pin] = InputType;
        else if (outputPins.count(pin))
            component_links[pin] = OuputType;
        else
            component_links[pin] = UndefinedType;
    }

    //link the internal componens
    for (const auto& info : gateInfos) {
        //mmmm func pointers
        auto gate = factory();

        //link subgate input pins (numbered 1,2,3... inside that gate)
        // to the chip external input pins in info.InputPins
        for (std::size_t i = 0; i < info.InputPins.size(); ++i) {
            //confusig so think like this  setLink(sub_gate_pin, target_component, target_pin)
            gate->setLink(i + 1, *this, info.InputPins[i]);
        }

        //link the sub gate output pin to the main gate output pin (not sure if we'll use this)
        gate->setLink(info.OutputPin, *this, info.GateOutputPin);

        //we emember which external output pin belongs to which gate
        //tricky stuff had to look this this up, since we since automatically allocated, size is actually the index of when we added it (so the index of where we'll find the gate)
        //tells us, for a given external output pin, which internal gate produces it
        m_outputToGate[info.GateOutputPin] = m_gates.size();

        //store the gate together with its internal output pin number
        //we need the internal output pin later in compute()
        m_gates.push_back({std::move(gate), info.OutputPin});
    }
}

nts::Tristate nts::AGateComponent::compute(size_t pin)
{
    // we check if the requested pin is one of our external output pins
    auto it = m_outputToGate.find(static_cast<int>(pin));
    if (it != m_outputToGate.end()) {
        //get the gate holder
        const auto& holder = m_gates[it->second];
        //forward the comput to the inside gate
        return holder.comp->compute(holder.subOutputPin);
    }
    //default behaviour on gate (cus mini gate neeed acces to inputs so the'll call on our inputs)
    //also a way to going over the overwriting of computs
    return AComponent::compute(pin);
}

