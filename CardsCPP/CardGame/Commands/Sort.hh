#ifndef CARDGAME_SORT_HH
#define CARDGAME_SORT_HH

#include "../Command.hh"

class Sort : public Command {
    Game *game_;

public:
    explicit Sort(Game *game) : game_(game) {}

    ~Sort() override = default;

    void execute() override {
        if (game_->get_hand().is_dealt()) {
            game_->get_hand().clear();
        }
        game_->get_deck().sort();
        game_->get_deck().print();
    }
};

#endif //CARDGAME_SORT_HH
