/*
 EPITECH PROJECT, 2026
 nanotekspice
 File description:
 Component4512
*/

#include "Component4512.hpp"
#include "IComponent.hpp"

/*
# 8 Channel Data Selector (4512)
#
#          in_3 -4-+ +-5- in_4
#        in_2 -3-+ | | +-6- in_5
#      in_1 -2-+ | | | | +-7- in_6
#    in_0 -1-+ | | | | | | +-9- in_7
#            | | | | | | | |
#          +-v-v-v-v-v-v-v-v-+
#          |                 |
# in_a -11->                 <-10- inhibit
#          |                 |
# in_b -12->                 |
#          |                 |
# in_c -13->                 <-15- enable
#          |                 |
#          +-4512---v--------+
#                   |
#                   +-14- out_data
*/

nts::Component4512::Component4512()
{
    component_links = {
        {1, InputType}, //in_0
        {2, InputType}, //in_1
        {3, InputType}, //in_2
        {4, InputType},//in_3
        {5, InputType},//in_4
        {6, InputType},//in_5
        {7, InputType},//in_6
        {8, UndefinedType}, //not connected to anything
        {9, InputType}, //in_7
        {10, InputType}, //inhibit
        {11, InputType}, //in_a
        {12, InputType}, //in_b
        {13, InputType}, //in_c
        {14, OutputType}, //out_data
        {15, InputType} //enable
    };
}

/*
|     Address Inputs    |  Control Inputs   |  Output   |
---------------------------------------------------------
|   C   |   B   |   A   |  Inhibit  |   OE  |   Z       |
---------------------------------------------------------
|   0   |   0   |   0   |   0       |   0   |   X0      |
|   0   |   0   |   1   |   0       |   0   |   X1      |
|   0   |   1   |   0   |   0       |   0   |   X2      |
|   0   |   1   |   1   |   0       |   0   |   X3      |
|   1   |   0   |   0   |   0       |   0   |   X4      |
|   1   |   0   |   1   |   0       |   0   |   X5      |
|   1   |   1   |   0   |   0       |   0   |   X6      |
|   1   |   1   |   1   |   0       |   0   |   X7      |
|   Ç   |   Ç   |   Ç   |   1       |   0   |   0       |
|   Ç   |   Ç   |   Ç   |   Ç       |   1   |   Hi-Z    |

Ç = Don’t care

Hi-Z = TRI-STATE condition (i'm unsure if this means undefined or if it means we should disconnect the output from the circuit, but since we don't have a way to represent disconnection, we'll just return undefined)

Xn = Data at input n
*/
nts :: Tristate nts::Component4512::compute ( std :: size_t pin )
{
    Tristate enable = getLink(15);
    Tristate inhibit = getLink(10);

    if (enable != False || inhibit == Undefined)
        return Undefined;

    if (inhibit == True)
        return False;

    //what i have observed:
    //when enable is true we return undefined, regardless of the value of inhibit
    //when inhibit is true we return false.
    //both inhibit and enable have to be false to be able to get to any part of the code
    //if inhibit or enable is undefined we return undefined.
    //we need to have all the input a through c to be defined to not return undefined

    //we build the index of the input we need to return based on the address inputs
    int index = 0;
    Tristate possibilities[3] = {getLink(13), getLink(12), getLink(11)};
    //for (int i = 0; i < 3; i++) {
    //    if (possibilities[i] == Undefined) //if one of the address inputs is undefined, the output is undefined
    //        return Undefined;
    //}
    if (possibilities[0] == nts::True) //C is the most significant bit
        index |= 4;
    if (possibilities[1] == nts::True) //B is the middle bit
        index |= 2;
    if (possibilities[2] == nts::True) //A is the least significant bit
        index |= 1;
    int return_pin = index + 1; //index max value is 7, so we add 1 to get the corresponding input pin (since our input pins are 1-indexed)
    if (return_pin >= 8)
        return_pin += 1;

    return getLink(return_pin);
    //index we just computed (we add 1 because our inputs are 1-indexed)
}
