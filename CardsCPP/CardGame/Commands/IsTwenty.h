#ifndef CARDGAME_ISTWENTY_H
#define CARDGAME_ISTWENTY_H

#include <iostream>
#include "../Command.hh"
#include "../GameError.hh"

class IsTwenty : public Command {
    Santase *game_;
    const char suit_;

public:
    IsTwenty(Santase *game, const char suit) : game_(game), suit_(suit) {}

    void execute() override {
        if (!game_->get_hand().is_dealt()) {
            throw GameError("ERROR: Unknown command.");
        }
        std::cout << std::boolalpha << game_->is_twenty(suit_) << std::noboolalpha << std::endl;
    }
};

#endif //CARDGAME_ISTWENTY_H
