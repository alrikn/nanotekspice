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
#include <algorithm>
#include <cctype>
#include <functional>
#include <unordered_map>
#include <vector>

//helpers

static std::string remove_inline_comment(const std::string &line)
{
    auto pos = line.find('#');

    if (pos == std::string::npos)
        return line;
    return line.substr(0, pos);
}

static std::vector<std::string> split_ws(const std::string &s)
{
    std::istringstream iss(s);
    std::vector<std::string> out;
    std::string tok;

    while (iss >> tok)
        out.push_back(tok);
    return out;
}

nts::Parser::Parser(const std::string &file) : file_path(file), file_ptr(file)
{
    if (!file_ptr.is_open())
        throw std::runtime_error("Could not open file: " + file_path);
}

std::string nts::Parser::trim(const std::string &line)
{
    size_t start = line.find_first_not_of(" \t");

    if (start == std::string::npos)
        return "";

    size_t end = line.find_last_not_of(" \t");
    return line.substr(start, end - start + 1);
}

bool nts::Parser::is_comment_or_empty(const std::string &line)
{
    std::string t = trim(line);
    return t.empty() || t[0] == '#';
}

void nts::Parser::parse_chipset_line(const std::string &line)
{


}

void nts::Parser::parse_link_line(const std::string &line)
{

}

void nts::Parser::parse_chipsets()
{
    std::string line;

    while(std::getline(file_ptr, line)) {
        std::string t = trim(remove_inline_comment(line));
        if (is_comment_or_empty(t))
            continue;

        // easiest way; can move back to parser if thats clearer
        if(t == ".links:") {
            //if(!found_chipsets)
            //    throw std::runtime_error("missing .chipsets section");
            if(found_links)
                throw std::runtime_error("duplicate .links section");
            found_links = true;
            parse_links();
            return;
        }
        parse_chipset_line(line);
    }
}

void nts::Parser::parse_links()
{
    std::string line;

    while (std::getline(file_ptr, line)) {
        std::string t = trim(remove_inline_comment(line));
        if (is_comment_or_empty(t))
            continue;
        parse_link_line(line);
    }

}

void nts::Parser::run_parser()
{
    std::string line;

    while(std::getline(file_ptr, line)) {
        std::string t = trim(remove_inline_comment(line));

        if(is_comment_or_empty(t))
            continue;
        if(t == ".chipsets:") {
            if(found_chipsets)
                throw std::runtime_error("duplicate .chipsets section"); // will change errors later to comply with the pdf
            found_chipsets = true;
            parse_chipsets();
            continue;
        }
        // moved inside parse_chipsets()
        /*if(t == ".links:") {
            if(!found_chipsets)
                throw std::runtime_error("missing .chipsets section");
            if(found_links)
                throw std::runtime_error("duplicate .links section");
            found_links = true;
            parse_links();
            continue;
        }*/
        // non-section line at top is a syntax error
        throw std::runtime_error("Unexpected line outside sections: '" + line + "'");
    }
    if(!found_chipsets || !found_links)
        throw std::runtime_error("missing section");
}

nts::Circuit &nts::Parser::getCircuit()
{
    return circuit;
}