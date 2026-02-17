/*
** EPITECH PROJECT, 2026
** bootstrap_nanotekspice
** File description:
** main
*/

#include "Circuit.hpp"
#include "Component4069.hpp"
#include "Component4081.hpp"
#include "IComponent.hpp"
#include "AComponent.hpp"
#include "AndComponent.hpp"
#include "NotComponent.hpp"
#include "TrueComponent.hpp"
#include "FalseComponent.hpp"
#include "UserInputComponent.hpp"
#include "UserOutputComponent.hpp"




#include <memory>

#include <ostream>
std :: ostream & operator <<( std :: ostream & s , nts :: Tristate v)
{
    if (v == nts::Undefined)
        s << "U";
    if (v == nts::True)
        s << "1";
    if (v == nts::False)
        s << "0";
    return s;
}


void test_func()
{
    nts::Circuit the_circuit;

    auto gate = std :: make_unique < nts :: Component4069 >() ;
    auto input_a = std :: make_unique < nts :: UserInputComponent >() ;
    auto input_b = std :: make_unique < nts :: UserInputComponent >() ;
    auto output_c = std :: make_unique < nts :: UserOutputComponent >() ;

    gate -> setLink (1 , * input_a , 1) ;
    //gate -> setLink (2 , * input_b , 1) ;
    //output_c -> setLink (1 , * gate , 3) ;
    output_c -> setLink (1 , * gate , 2) ;

    input_a->set_real_value(nts::False);
    input_b->set_real_value(nts::False);
    //we add them to the circuit
    the_circuit.addComponent("input_a", std::move(input_a), nts::InDisplayComponent);
    the_circuit.addComponent("input_b", std::move(input_b), nts::InDisplayComponent);
    the_circuit.addComponent("output_c", std::move(output_c), nts::OutDisplayComponent);
    the_circuit.addComponent("and_gate", std::move(gate), nts::NormalComponent);

    the_circuit.display();
    the_circuit.simulate(1);
    the_circuit.display();
}


int main ( void )
{
    //std :: unique_ptr<nts::IComponent>gate = std :: make_unique < nts :: AndComponent >() ;
    //std :: unique_ptr<nts::IComponent>input1 = std :: make_unique < nts :: FalseComponent >() ;
    //std :: unique_ptr<nts::IComponent>input2 = std :: make_unique < nts :: TrueComponent >() ;
    //std :: unique_ptr<nts::IComponent>inverter = std :: make_unique < nts :: NotComponent >() ;
    //gate -> setLink (1 , * input1 , 1) ;
    //gate -> setLink (2 , * input2 , 1) ;
    //inverter -> setLink (1 , * gate , 3) ;
    //std :: cout << " !( " << input1 -> compute (1) << " && " << input2 -> compute (1) << ") -> " <<
    //inverter -> compute (2) << std :: endl ;

    test_func();
}