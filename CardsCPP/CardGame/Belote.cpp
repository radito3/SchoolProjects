#include "Belote.hh"
#include "Command.hh"
#include "Commands/IsBelote.hh"

#include <unordered_map>

std::unordered_map<std::string, Command *> Belote::build_commands() const {
    std::unordered_map<std::string, Command*> commands = get_common_commands();

    commands.emplace("belote?", new IsBelote((Belote *) this));
//    commands.emplace("tierce?", new IsTierce((Belote *) this));
//    commands.emplace("quarte?", new IsQuarte((Belote *) this));
//    commands.emplace("quint?", new IsQuint((Belote *) this));

    return commands;
}
