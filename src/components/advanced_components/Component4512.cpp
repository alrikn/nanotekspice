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
        {1, InputType},
        {2, InputType},
        {3, InputType},
        {4, InputType},
        {5, InputType},
        {6, InputType},
        {7, InputType},
        {8, InputType},
        {9, InputType},
        {10, InputType},
        {11, InputType},
        {12, InputType},
        {13, InputType},
        {14, OutputType},
        {15, InputType}
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

    if (enable != False)
        return Undefined;

    if (inhibit == True)
        return False;
    if (inhibit == Undefined)
        return Undefined;
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
    return getLink(index + 1); //we return the value of the input at the
    //index we just computed (we add 1 because our inputs are 1-indexed)
}
