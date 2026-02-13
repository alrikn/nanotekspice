/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Parser
*/

#ifndef INCLUDED_PARSER_HPP
    #define INCLUDED_PARSER_HPP

#include "Circuit.hpp"
namespace nts {

class Parser
{
    private:
    protected:
        Circuit circuit;
        bool found_links = false;
        bool found_chipsets = false;
        std::string file_path;

    public:
        Parser(Circuit circuit, std::string file) : circuit(circuit), file_path(file) {}
        void parse_chipset();
        void parse_link();
        bool check_empty();
        ~Parser() = default;

};
}

#endif
