#ifndef CARDGAME_SHUFFLE_HH
#define CARDGAME_SHUFFLE_HH

#include "../Command.hh"

class Shuffle : public Command {
    Game *game_;

public:
    explicit Shuffle(Game *game) : game_(game) {}

    void execute() override {
        if (game_->get_hand().is_dealt()) {
            game_->get_hand().clear();
        }
        game_->get_deck().shuffle();
        game_->get_deck().print();
    }
};

#endif //CARDGAME_SHUFFLE_HH
