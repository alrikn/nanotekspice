/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** main_loop
*/

#include "ASpecialComponent.hpp"
#include "CLI_interface.hpp"
#include "Circuit.hpp"

using namespace nts;

// small helpers
static std::string trim(const std::string &s)
{
    size_t a = s.find_first_not_of(" \t\n");
    if (a == std::string::npos)
        return "";
    size_t b = s.find_last_not_of(" \t\n");
    return s.substr(a, b - a + 1);
}

static std::string strip_asterisks(const std::string &s)
{
    std::string out;

    for (char c : s)
        if (c != '*')
            out.push_back(c);
    return out;
}

static bool iequals(const std::string &a, const std::string &b)
{
    if (a.size() != b.size())
        return false;
    for (size_t i = 0; i < a.size(); i++) //probs a better way to do this but am tired rn
        if (std::tolower((unsigned char)a[i]) != std::tolower((unsigned char)b[i]))
            return false;
    return true;
}

static bool parse_tristate(const std::string &s, Tristate &out)
{
    if (s.empty()) return false;
    if (iequals(s, "1") || iequals(s, "true")) { out = Tristate::True; return true; }
    if (iequals(s, "0") || iequals(s, "false")) { out = Tristate::False; return true; }
    if (iequals(s, "u") || iequals(s, "undefined")) { out = Tristate::Undefined; return true; }
    return false;
}

/** end of helper funcs, start of where the real magic happens (might need to put all the helper funcs somewhere sles theres starting to be a lot of them) */

void CLI_interface::parse_command(const std::string &raw_line)
{
    std::string line = trim(strip_asterisks(raw_line));
    if (line.empty()) {
        type = CmdType::Unknown;
        return;
    }

    // exact word commands
    if (iequals(line, "exit")) {
        type = CmdType::Exit;
        return;
    }
    if (iequals(line, "simulate")) {
        type = CmdType::Simulate;
        return;
    }
    if (iequals(line, "display")) {
        type = CmdType::Display;
        return;
    }

    //otherwise this means that its an assignement
    auto pos = line.find('=');
    if (pos != std::string::npos) {
        std::string name = trim(line.substr(0, pos));
        std::string val = trim(line.substr(pos + 1));
        if (!name.empty() && !val.empty()) {
            type = CmdType::Assignment;
            lhs = std::move(name);
            rhs = std::move(val);
            return;
        }
    }

    type = CmdType::Unknown;
}

bool CLI_interface::handle_exit()
{
    return false; //to break out of loop
}

bool CLI_interface::handle_simulate()
{
    tick++;
    try {
        _circuit->simulate(tick);
    } catch (const std::exception &e) {
        //TODO: do our own exception thinggy
        std::cout << "simulate failed: " << e.what() << '\n';
    }
    return true;
}

bool CLI_interface::handle_display()
{
    if (tick > 0)
        std::cout << "tick: " << tick << '\n';
    try {
        _circuit->display();
    } catch (const std::exception &e) { //TODO: proper error management class
        std::cout << "display failed: " << e.what() << '\n';
    }
    return true;
}

bool CLI_interface::handle_assignment()
{
    Tristate t;
    std::string value = rhs;
    std::string name = lhs;

    if (!parse_tristate(value, t)) {
        std::cout << "Invalid value '" << value << "'. Use 1, 0, or U (or true/false/undefined).\n";
        return true;
    }

    //we can only get this on input types like clock or the input
    try {
        ClassType ct = _circuit->getType(name);
        if (ct != InDisplayComponent && ct != nts::ClockComponentDisplay) {
            std::cout << "Component '" << name << "' is not settable (must be input/clock)\n";
            return true;
        }

        //we have to dynamic cast the Icomponent to Aspecial compmponent to make use of the set val
        std::unique_ptr<IComponent> &comp = _circuit->getComponent(name);
        ASpecialComponent *special = dynamic_cast<ASpecialComponent*>(comp.get());
        if (!special) {
            std::cout << "Component '" << name << "' cannot be cast to ASpecialComponent\n";
            return true;
        }

        special->set_real_value(t);
    } catch (const std::out_of_range &) { //very cool can call multiple catch on specific things
        std::cout << "Unknown component '" << name << "'\n";
    } catch (const std::exception &e) {
        std::cout << "Error setting '" << name << "': " << e.what() << '\n';
    }
    return true;
}

int CLI_interface::run_loop(Circuit &circuit)
{
    _circuit = &circuit;
    std::string raw;

    handle_simulate(); //simulate once at start to update all the outputs based on the initial inputs before we display for the first time
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, raw))
            return 0;

        parse_command(raw);

        switch (type) {
            case CmdType::Exit:
                if (!handle_exit())
                    return 0;
                break;

            case CmdType::Simulate:
                handle_simulate();
                break;

            case CmdType::Display:
                handle_display();
                break;

            case CmdType::Assignment:
                handle_assignment();
                break;

            case CmdType::Unknown:
            default:
                //if not blank line err
                if (!trim(strip_asterisks(raw)).empty())
                    std::cout << "Unknown command: '" << raw << "'\n";
                break;
        }
    }
    return 0;
}
