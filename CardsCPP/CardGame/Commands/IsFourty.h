#ifndef CARDGAME_ISFOURTY_H
#define CARDGAME_ISFOURTY_H

#include <iostream>
#include "../Command.hh"
#include "../GameError.hh"

class IsFourty : public Command {
    Santase *game_;
    char suit_;
    const char *suit_full_name_;

public:
    IsFourty(Santase *game, char suit, const char *suit_full_name)
            : game_(game), suit_(suit), suit_full_name_(suit_full_name) {}

    bool matches(const std::string &command) override {
        std::string cmd_name("fourty?:");
        cmd_name.append(suit_full_name_);
        return command == cmd_name;
    }

    void execute() override {
        if (!game_->get_hand().is_dealt()) {
            throw GameError("ERROR: Unknown command.");
        }
        std::cout << std::boolalpha << game_->is_fourty(suit_) << std::noboolalpha << std::endl;
    }
};

#endif //CARDGAME_ISFOURTY_H
