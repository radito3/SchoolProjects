#include "Santase.hh"
#include "Command.hh"

#include <unordered_map>

std::unordered_map<std::string, Command *> Santase::build_commands() const {
    std::unordered_map<std::string, Command*> commands = get_common_commands();

    //TODO add santase commands

    return commands;
}
