#ifndef CARDGAME_HIGHESTOFSUIT_H
#define CARDGAME_HIGHESTOFSUIT_H

#include <iostream>
#include "../Command.hh"
#include "../GameError.hh"

class HighestOfSuit : public Command {
    Belote* game_;
    const char suit_;

public:
    HighestOfSuit(Belote* game, const char suit) : game_(game), suit_(suit) {}

    void execute() override {
        if (!game_->get_hand().is_dealt()) {
            throw GameError("ERROR: Unknown command.");
        }
        game_->print_highest_of_suit(suit_);
    }
};

#endif //CARDGAME_HIGHESTOFSUIT_H
