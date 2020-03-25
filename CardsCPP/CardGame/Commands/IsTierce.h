#ifndef CARDGAME_ISTIERCE_H
#define CARDGAME_ISTIERCE_H

#include <iostream>
#include "../Command.hh"
#include "../GameError.hh"

class IsTierce : public Command {
    Belote* game_;

public:
    explicit IsTierce(Belote* game) : game_(game) {}

    ~IsTierce() override = default;

    void execute() override {
        if (!game_->get_hand().is_dealt()) {
            throw GameError("ERROR: Unknown command.");
        }
        std::cout << std::boolalpha << game_->is_tierce() << std::noboolalpha << std::endl;
    }
};

#endif //CARDGAME_ISTIERCE_H
