#ifndef CARDGAME_REMAINING_HH
#define CARDGAME_REMAINING_HH

#include <iostream>
#include "../Command.hh"

class Remaining : public Command {
    Game* game_;

public:
    explicit Remaining(Game* game) : game_(game) {}

    ~Remaining() override = default;

    void execute() override {
        if (!game_->get_hand().is_dealt()) {
            throw GameError("ERROR: Unknown command");
        }
        std::cout << game_->get_hand().size() << std::endl;
    }
};

#endif //CARDGAME_REMAINING_HH
