#include "Belote.hh"
#include "Command.hh"
#include "Commands/IsBelote.hh"
#include "Commands/IsTierce.h"
#include "Commands/IsQuarte.h"
#include "Commands/IsQuint.h"

#include <unordered_map>

std::unordered_map<std::string, Command *> Belote::get_commands() const {
    std::unordered_map<std::string, Command*> commands = std::move(get_common_commands());

    commands.emplace("belote?", new IsBelote((Belote *) this));
    commands.emplace("tierce?", new IsTierce((Belote *) this));
    commands.emplace("quarte?", new IsQuarte((Belote *) this));
    commands.emplace("quint?", new IsQuint((Belote *) this));

    return commands;
}
