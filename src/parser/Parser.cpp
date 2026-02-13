/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Parser
** The parse only handles the file, not the cli
*/

#include "Parser.hpp"
#include <csignal>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

nts::Parser::Parser(Circuit circuit, std::string file) : circuit(circuit), file_path(file), file_ptr(file)
{
    if (!file_ptr.is_open())
        throw std::runtime_error("Could not find file");
}

void nts::Parser::parse_chipset()
{
    
}

bool nts::Parser::check_empty()
{

}

void nts::Parser::GetNextLine()
{

}

void nts::Parser::run_parser()
{
    std::string line;

    while (std::getline(file_ptr, line)) {
        std::stringstream curr_line = std::stringstream(line);

    }
}
