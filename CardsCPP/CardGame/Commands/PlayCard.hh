#ifndef CARDGAME_PLAYCARD_HH
#define CARDGAME_PLAYCARD_HH

#include <iostream>
#include "../Command.hh"

class PlayCard : public Command {
    Game* game_;

public:
    explicit PlayCard(Game* game) : game_(game) {}

    void execute() override {
        if (!game_->get_hand().is_dealt()) {
            throw GameError("ERROR: Unknown command");
        }
        const Card* first = game_->get_hand().draw_first();
        std::cout << *first << std::endl;
        delete first;
    }
};

#endif //CARDGAME_PLAYCARD_HH
