/*
** EPITECH PROJECT, 2026
** bootstrap_nanotekspice
** File description:
** main
*/

#include "IComponent.hpp"
#include "AComponent.hpp"

#include <ostream>
std :: ostream & operator <<( std :: ostream & s , nts :: Tristate v)
{
/* Implement me */
}
int main ( void )
{
std :: unique_ptr<nts::IComponent>gate = std :: make_unique < nts :: AndComponent >() ;
std :: unique_ptr<nts::IComponent>input1 = std :: make_unique < nts :: FalseComponent >() ;
std :: unique_ptr<nts::IComponent>input2 = std :: make_unique < nts :: TrueComponent >() ;
std :: unique_ptr<nts::IComponent>inverter = std :: make_unique < nts :: NotComponent >() ;
gate -> setLink (1 , * input1 , 1) ;
gate -> setLink (2 , * input2 , 1) ;
inverter -> setLink (1 , * gate , 3) ;
std :: cout << " !( " << input1 -> compute (1) << " && " << input2 -> compute (1) << ") -> " <<
inverter -> compute (2) << std :: endl ;
}