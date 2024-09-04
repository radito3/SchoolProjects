#ifndef CARDGAME_ISTWENTY_H
#define CARDGAME_ISTWENTY_H

#include <iostream>
#include "../Command.hh"
#include "../GameError.hh"

class IsTwenty : public Command {
    Santase *game_;
    Card::Suit suit_;
    const char *suit_full_name_;

public:
    IsTwenty(Santase *game, Card::Suit suit, const char *suit_full_name)
            : game_(game), suit_(suit), suit_full_name_(suit_full_name) {}

    bool matches(const std::string &command) override {
        std::string cmd_name("twenty?:");
        cmd_name.append(suit_full_name_);
        return command == cmd_name;
    }

    void execute() override {
        if (!game_->get_hand().is_dealt()) {
            throw GameError("ERROR: Unknown command.");
        }
        std::cout << std::boolalpha << game_->is_twenty(suit_) << std::noboolalpha << std::endl;
    }
};

#endif //CARDGAME_ISTWENTY_H
