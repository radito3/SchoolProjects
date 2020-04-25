#ifndef CARDGAME_DEAL_HH
#define CARDGAME_DEAL_HH

#include "../Command.hh"

class Deal : public Command {
    Game *game_;

public:
    explicit Deal(Game *game) : game_(game) {}

    void execute() override {
        game_->get_hand().deal(game_->get_deck());
        game_->get_hand().print();
    }
};

#endif //CARDGAME_DEAL_HH
