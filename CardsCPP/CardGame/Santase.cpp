#include "Santase.hh"
#include "Command.hh"
#include "Commands/IsFourty.h"
#include "Commands/IsTwenty.h"

#include <unordered_map>

std::unordered_map<std::string, Command *> Santase::get_commands() const {
    std::unordered_map<std::string, Command *> commands = std::move(get_common_commands());

    commands.emplace("fourty?:spades", new IsFourty((Santase *) this, 'S'));
    commands.emplace("fourty?:hearts", new IsFourty((Santase *) this, 'H'));
    commands.emplace("fourty?:diamonds", new IsFourty((Santase *) this, 'D'));
    commands.emplace("fourty?:clubs", new IsFourty((Santase *) this, 'C'));
    commands.emplace("twenty?:spades", new IsTwenty((Santase *) this, 'S'));
    commands.emplace("twenty?:hearts", new IsTwenty((Santase *) this, 'H'));
    commands.emplace("twenty?:diamonds", new IsTwenty((Santase *) this, 'D'));
    commands.emplace("twenty?:clubs", new IsTwenty((Santase *) this, 'C'));

    return commands;
}
