#ifndef CARDGAME_ISQUINT_H
#define CARDGAME_ISQUINT_H

#include <iostream>
#include "../Command.hh"
#include "../GameError.hh"

class IsQuint : public Command {
    Belote* game_;

public:
    explicit IsQuint(Belote* game) : game_(game) {}

    ~IsQuint() override = default;

    void execute() override {
        if (!game_->get_hand().is_dealt()) {
            throw GameError("ERROR: Unknown command.");
        }
        std::cout << std::boolalpha << game_->is_quint() << std::noboolalpha << std::endl;
    }
};

#endif //CARDGAME_ISQUINT_H
