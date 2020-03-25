#ifndef CARDGAME_PLAYCARD_HH
#define CARDGAME_PLAYCARD_HH

#include <iostream>
#include "../Command.hh"

class PlayCard : public Command {
    Game* game_;

public:
    explicit PlayCard(Game* game) : game_(game) {}

    ~PlayCard() override = default;

    void execute() override {
        if (!game_->get_hand().is_dealt()) {
            throw GameError("ERROR: Unknown command");
        }
        std::cout << game_->get_hand().draw_first().to_string() << std::endl;
    }
};

#endif //CARDGAME_PLAYCARD_HH
