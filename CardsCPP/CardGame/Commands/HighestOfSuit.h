#ifndef CARDGAME_HIGHESTOFSUIT_H
#define CARDGAME_HIGHESTOFSUIT_H

#include <iostream>
#include <format>
#include "../Command.hh"
#include "../GameError.hh"

class HighestOfSuit : public Command {
    Belote *game_;
    Card::Suit suit_;
    const char *suit_full_name_;

public:
    HighestOfSuit(Belote *game, Card::Suit suit, const char *suit_full_name)
            : game_(game), suit_(suit), suit_full_name_(suit_full_name) {}

    bool matches(const std::string_view &command) override {
        return command == std::format("highest_of_suit:{}", suit_full_name_);
    }

    void execute() override {
        if (!game_->get_hand().is_dealt()) {
            throw GameError("ERROR: Unknown command.");
        }
        game_->print_highest_of_suit(suit_);
    }
};

#endif //CARDGAME_HIGHESTOFSUIT_H
