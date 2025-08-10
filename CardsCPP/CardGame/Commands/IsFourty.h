#ifndef CARDGAME_ISFOURTY_H
#define CARDGAME_ISFOURTY_H

#include <iostream>
#include <format>
#include "../Command.hh"
#include "../GameError.hh"

class IsFourty : public Command {
    Santase *game_;
    Card::Suit suit_;
    const char *suit_full_name_;

public:
    IsFourty(Santase *game, Card::Suit suit, const char *suit_full_name)
            : game_(game), suit_(suit), suit_full_name_(suit_full_name) {}

    bool matches(const std::string_view &command) override {
        return command == std::format("fourty?:{}", suit_full_name_);
    }

    void execute() override {
        if (!game_->get_hand().is_dealt()) {
            throw GameError("ERROR: Unknown command.");
        }
        std::cout << std::boolalpha << game_->is_fourty(suit_) << std::noboolalpha << std::endl;
    }
};

#endif //CARDGAME_ISFOURTY_H
