/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Component4069
*/

/*
# NOT logic gates (4069)
#
#           +----4069----+
# in_01  -1-|>--+    ign-|-14-
#           |  _|_       |
#           |  \ /   +--<|-13- in_13
#           |   v   _|_  |
#           |   O   \ /  |
#           |   |    v   |
# out_02 -2-|<--+    O   |
#           |        |   |
# in_03  -3-|>--+    +-->|-12- out_12
#           |  _|_       |
#           |  \ /   +--<|-11- in_11
#           |   v   _|_  |
#           |   O   \ /  |
#           |   |    v   |
# out_04 -4-|<--+    O   |
#           |        |   |
# in_05  -5-|>--+    +-->|-10- out_10
#           |  _|_       |
#           |  \ /   +--<|-9-  in_09
#           |   v   _|_  |
#           |   O   \ /  |
#           |   |    v   |
# out_06 -6-|<--+    O   |
#           |        |   |
#        -7-|-ign    +-->|-8-  out_08
#           +------------+
*/

#include "Component4069.hpp"
#include "AGateComponent.hpp"
#include "NotComponent.hpp"

static std::unique_ptr<nts::NotComponent> make_func()
{
    return std::make_unique<nts::NotComponent>();
}

nts::Component4069::Component4069() : nts::AGateComponent({
                    {{1},  2, 2},
                    {{3},  4, 2},
                    {{5},  6, 2},
                    {{9},  8, 2},
                    {{11}, 10, 2},
                    {{13}, 12, 2}
                },
                make_func
            )
{
    //i could put this entire thing in hpp but then it would be inconsistent
}