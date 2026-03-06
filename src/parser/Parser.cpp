/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Parser
** The parse only handles the file, not the cli
*/

#include "Parser.hpp"
#include "Circuit.hpp"

#include <csignal>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <cctype>

#include <vector>
#include "Factory.hpp" //Included header Factory.hpp is not used directly


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

// helper parse "name:pin" -> {name, pin}
static std::pair<std::string, std::size_t> parse_endpoint(const std::string &ep)
{
    auto pos = ep.find(':');
    if (pos == std::string::npos)
        throw std::runtime_error("Invalid link endpoint '" + ep + "' (missing ':')");

    std::string compName = ep.substr(0, pos);
    std::string pinStr = ep.substr(pos + 1);

    if (compName.empty())
        throw std::runtime_error("Invalid link endpoint '" + ep + "' (empty component name)");
    if (pinStr.empty())
        throw std::runtime_error("Invalid link endpoint '" + ep + "' (empty pin)");

    for (char c : pinStr)
        if (!std::isdigit(static_cast<unsigned char>(c)))
            throw std::runtime_error("Invalid pin number in '" + ep + "'");

    std::size_t pin = static_cast<std::size_t>(std::stoul(pinStr));
    if (pin == 0)
        throw std::runtime_error("Pin number must be >= 1 in '" + ep + "'");

    return {compName, pin};
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
    std::string clean = trim(remove_inline_comment(line));
    if (clean.empty())
        return;

    std::vector<std::string> tokens = split_ws(clean);
    if (tokens.size() != 2)
        throw std::runtime_error("Invalid chipset declaration: '" + line + "'");

    const std::string &type = tokens[0];
    const std::string &name = tokens[1];
    // created in factory!!
    auto created = nts::Factory::create(type);

    try {
        // std::move transfers ownership to addComponent since created.first is a
        //unique pointer and cant be copied, just moved
        circuit.addComponent(name, std::move(created.first), created.second);
    } catch (const std::exception &e) { // if addComponent throws exception
        throw std::runtime_error(std::string("Failed to add component '") + name + "': " + e.what());
    }
}

void nts::Parser::parse_link_line(const std::string &line)
{
    std::string cleaned = trim(remove_inline_comment(line));
    if (cleaned.empty())
        return;

    std::vector<std::string> tokens = split_ws(cleaned);
    if (tokens.size() != 2)
        throw std::runtime_error("Invalid link declaration: '" + line + "'");

    // helper ^
    auto left = parse_endpoint(tokens[0]);
    auto right = parse_endpoint(tokens[1]);

    std::unique_ptr<IComponent> &leftComp = circuit.getComponent(left.first);
    std::unique_ptr<IComponent> &rightComp = circuit.getComponent(right.first);

    //alrik code to check if the pins can actually go together
    nts::PinType leftType = leftComp->get_type(left.second);
    nts::PinType rightType = rightComp->get_type(right.second);

    bool correct_combo = (leftType + rightType) == valid_pin_combination;

    if (!correct_combo)
        throw std::runtime_error("Invalid link: pins must be connected Output <-> Input");

    leftComp->setLink(left.second, *rightComp, right.second);
    rightComp->setLink(right.second, *leftComp, left.second);
}

void nts::Parser::parse_chipsets()
{
    std::string line;
    //TODO: if chipsets is empty make an error

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
    //if chipset is empty (as in no components were declared) throw error
    //if (circuit.getComponents().empty())
    //    throw std::runtime_error("No components declared in .chipsets section");

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
