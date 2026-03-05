/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Component2716
*/

#include "Component2716.hpp"
#include "IComponent.hpp"
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <stdexcept>

/*
# 2048 Bytes ROM (2716)
#
#             addr_05 -3-+
#           addr_04 -4-+ | +-2- addr_06
#         addr_03 -5-+ | | | +-1- addr_07
#       addr_02 -6-+ | | | | | +-23- addr_08
#     addr_01 -7-+ | | | | | | | +-22- addr_09
#   addr_00 -8-+ | | | | | | | | | +-19- addr_10
#              | | | | | | | | | | |
#            +-v-v-v-v-v-v-v-v-v-v-v-+
#            |                       |
# enable -18->                  ign -<-12-
#            |                       |
#        -21->- ign             ign -<-19-
#            |                       |
#   read -20->                  ign -<-24-
#            | 2716 ROM              |
#            +----v-v-v-v-v-v-v-v----+
#                 | | | | | | | |       
#        out_0 -9-+ | | | | | | +-17- out_7
#         out_1 -10-+ | | | | +-16- out_6
#           out_2 -11-+ | | +-15- out_5
#             out_3 -13-+ +-14- out_4

*/

nts::Component2716::Component2716()
{
    component_links = {
        //inputs
        {1, InputType}, //addr_07
        {2, InputType}, //addr_06
        {3, InputType}, //addr_05
        {4, InputType}, //addr_04
        {5, InputType}, //addr_03
        {6, InputType}, //addr_02
        {7, InputType}, //addr_01
        {8, InputType}, //addr_00
        {23, InputType}, //addr_08
        {22, InputType}, //addr_09
        {19,InputType}, //addr_10

        //main input
        {18, InputType}, //enable
        {20, InputType}, //read

        //outputs
        {9, OutputType}, //out_0
        {10, OutputType}, //out_1
        {11, OutputType}, //out_2
        {13, OutputType}, //out_3
        {14, OutputType}, //out_4
        {15, OutputType}, //out_5
        {16, OutputType}, //out_6
        {17, OutputType}, //out_7

    };

    //now we must load the rom.
    std::ifstream rom_file("./rom.bin", std::fstream::in);

    if (!rom_file.is_open())
        throw std::runtime_error("Could not open rom file: ./rom.bin");


    //this will write more than 2048 chars sinvce it thinks we want bytes instead of bits.
    //we can solve this by just reading 2048 chars and separating them all into bits inside of our array

    for (int i = 0; i < 2048; i++) {
        uint8_t byte;
        rom_file.get((char&)byte);
        if (rom_file.gcount() == -1)
            throw std::runtime_error("Error reading rom file: ./rom.bin");

        for (int bit = 0; bit < 8; bit++) {
            _memory[i * 8 + bit] = (byte >> (7 - bit)) & 1; //we shift the byte to get the value of each bit and store it in our memory array
        }
    }
    rom_file.close();
}


nts :: Tristate nts::Component2716::compute ( std :: size_t pin )
{
    int address = 0;
    Tristate inputs[11] = {getLink(8), getLink(7), getLink(6), getLink(5), getLink(4), getLink(3), getLink(2), getLink(1), getLink(23), getLink(22), getLink(19)};
    Tristate enable = getLink(18);
    Tristate read = getLink(20);

    for (int i = 0; i < 11; i++) {
        if (inputs[i] == True)
            address |= (1 << i); //we build the address from the input bits, we shift 1 to the left by the appropriate amount and OR it with the current address
        else if (inputs[i] == Undefined) //if one of the address inputs is undefined, the output is undefined
            return Undefined;
    }
    if (enable == True || read == True) //if enable is not true or read is not true, the output is undefined
        return Undefined;
    //we return the value of the memory at the address we just computed, we need to return the specific bit of the byte that corresponds to the output pin

    size_t output_pins[8] = {9, 10, 11, 13, 14, 15, 16, 17};
    for (int i = 0; i < 8; i++) {
        if (pin == output_pins[i]) {
            //we return the value of the bit at the address we computed, we multiply the address by 8 to get the starting index of the byte in our memory array, and we add i to get the specific bit
            return _memory[address * 8 + i] ? True : False;
        }
    }
    return Undefined;
}
