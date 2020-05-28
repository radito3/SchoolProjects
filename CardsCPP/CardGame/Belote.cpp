#include "Belote.hh"
#include "Command.hh"
#include "Commands/IsBelote.hh"
#include "Commands/IsTierce.h"
#include "Commands/IsQuarte.h"
#include "Commands/IsQuint.h"
#include "Commands/HighestOfSuit.h"

#include <unordered_map>

std::unordered_map<std::string, Command *> Belote::get_commands() const {
    std::unordered_map<std::string, Command *> commands = std::move(get_common_commands());

    commands.emplace("highest_of_suit:spades", new HighestOfSuit((Belote *) this, 'S'));
    commands.emplace("highest_of_suit:hearts", new HighestOfSuit((Belote *) this, 'H'));
    commands.emplace("highest_of_suit:diamonds", new HighestOfSuit((Belote *) this, 'D'));
    commands.emplace("highest_of_suit:clubs", new HighestOfSuit((Belote *) this, 'C'));
    commands.emplace("belote?", new IsBelote((Belote *) this));
    commands.emplace("tierce?", new IsTierce((Belote *) this));
    commands.emplace("quarte?", new IsQuarte((Belote *) this));
    commands.emplace("quint?", new IsQuint((Belote *) this));

    return commands;
}

const char Belote::belote_ranks[] = {'7', '8', '9', 'J', 'Q', 'K', 'T', 'A'};
