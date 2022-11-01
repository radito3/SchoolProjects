#ifndef CARDGAME_ISQUARTE_H
#define CARDGAME_ISQUARTE_H

#include <iostream>
#include "../Command.hh"
#include "../GameError.hh"

class IsQuarte : public Command {
    Belote *game_;

public:
    explicit IsQuarte(Belote *game) : game_(game) {}

    bool matches(const std::string &command) override {
        return command == "quarte?";
    }

    void execute() override {
        if (!game_->get_hand().is_dealt()) {
            throw GameError("ERROR: Unknown command.");
        }
        std::cout << std::boolalpha << game_->is_quarte() << std::noboolalpha << std::endl;
    }
};

#endif //CARDGAME_ISQUARTE_H
