#ifndef CARDGAME_ISFOURTY_H
#define CARDGAME_ISFOURTY_H

#include <iostream>
#include "../Command.hh"
#include "../GameError.hh"

class IsFourty : public Command {
    Santase* game_;
    const char suit_;

public:
    IsFourty(Santase* game, const char suit) : game_(game), suit_(suit) {}

    ~IsFourty() override = default;

    void execute() override {
        if (!game_->get_hand().is_dealt()) {
            throw GameError("ERROR: Unknown command.");
        }
        std::cout << std::boolalpha << game_->is_fourty(suit_) << std::noboolalpha << std::endl;
    }
};

#endif //CARDGAME_ISFOURTY_H
