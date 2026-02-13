/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Component4071
*/

/*
# OR logic gates (4071)
#
#           +---------4071---------+
# in_01  -1-|>-+---\       ignored-|-14-
#           |  | or |-+            |
# in_02  -2-|>-+---/  |     /---+-<|-13- in_13
#           |         |  +-| or |  |
# out_03 -3-|<--------+  |  \---+-<|-12- in_12
#           |            |         |
# out_04 -4-|<--------+  +-------->|-11- out_11
#           |         |            |
# in_05  -5-|>-+---\  |  +-------->|-10- out_10
#           |  | or |-+  |         |
# in_06  -6-|>-+---/     |  /---+-<|-9-  in_09
#           |            +-| or |  |
#        -7-|-ignored       \---+-<|-8-  in_08
#           +----------------------+

*/

#include "Component4071.hpp"
#include "Circuit.hpp"

nts::Component4071::Component4071()
{
    component_links = {
        //or1
        {1, InputType},{2, InputType},{3, OuputType},
        //or2
        {4, OuputType},{5, InputType},{6, InputType},
        //ignored
        {7,UndefinedType},
        //or3
        {8, InputType},{9, InputType},{10, OuputType},
        //or4
        {11, OuputType},{12, InputType},{13, InputType},
        //ignored
        {14,UndefinedType},
    };

    or1.setLink(1, *this, 1);
    or1.setLink(2, *this, 2);
    or1.setLink(3, *this, 3);

    //OR2 -> pins 5,6 -> 4
    or2.setLink(1, *this, 5);
    or2.setLink(2, *this, 6);
    or2.setLink(3, *this, 4);

    //OR3 -> pins 8,9 -> 10
    or3.setLink(1, *this, 8);
    or3.setLink(2, *this, 9);
    or3.setLink(3, *this, 10);

    //OR4 -> pins 12,13 -> 11
    or4.setLink(1, *this, 12);
    or4.setLink(2, *this, 13);
    or4.setLink(3, *this, 11);

}

nts :: Tristate nts::Component4071::compute ( std :: size_t pin )
{
    switch (pin) {
        case 3:
            return or1.compute(3);
        case 4:
            return or2.compute(3);
        case 10:
            return or3.compute(3);
        case 11:
            return or4.compute(3);
        default:
            return Undefined;
    }
}
