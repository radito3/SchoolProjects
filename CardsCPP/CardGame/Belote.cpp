#include "Belote.hh"
#include "Command.hh"
#include "Commands/IsBelote.hh"

#include <unordered_map>

std::unordered_map<std::string, Command *> Belote::get_available_commands() const noexcept {
    std::unordered_map<std::string, Command*> commands = get_common_commands();

    commands.emplace("belote?", new IsBelote((Belote *) this));
//    commands.emplace("tierce?", new IsBelote((Belote *) this));
//    commands.emplace("quarte?", new IsBelote((Belote *) this));
//    commands.emplace("quint?", new IsBelote((Belote *) this));

    return commands;
}
