/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Parser
*/

#ifndef INCLUDED_PARSER_HPP
    #define INCLUDED_PARSER_HPP

#include "Circuit.hpp"
#include <fstream>
#include <sstream>
#include <string>
namespace nts {

class Parser
{
    private:
    protected:
        Circuit circuit;
        bool found_links = false;
        bool found_chipsets = false;
        std::string file_path;
        std::ifstream file_ptr;
        std::stringstream curr_line;

    public:
        Parser(Circuit circuit, std::string file);
        void parse_chipset();
        void parse_link();
        bool check_empty();
        void run_parser();
        void GetNextLine();
        ~Parser() = default;

};
}

#endif
