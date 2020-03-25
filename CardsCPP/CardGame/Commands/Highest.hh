#ifndef CARDGAME_HIGHEST_HH
#define CARDGAME_HIGHEST_HH

#include <iostream>
#include "../Command.hh"

class Highest : public Command {
    Game* game_;

public:
    explicit Highest(Game* game) : game_(game) {}

    ~Highest() override = default;

    void execute() override {
        if (!game_->get_hand().is_dealt()) {
            throw GameError("ERROR: Unknown command");
        }
        std::cout << game_->get_hand().draw_highest().to_string() << std::endl;
    }
};

#endif //CARDGAME_HIGHEST_HH
