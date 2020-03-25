#ifndef CARDGAME_DRAWTOPCARD_HH
#define CARDGAME_DRAWTOPCARD_HH

#include <iostream>
#include "../Command.hh"

class DrawTopCard : public Command {
    Game *game_;

public:
    explicit DrawTopCard(Game *game) : game_(game) {}

    ~DrawTopCard() override = default;

    void execute() override {
        if (game_->get_hand().is_dealt()) {
            game_->get_hand().clear();
        }
        std::cout << game_->get_deck().draw_top_card().to_string() << std::endl;
    }
};

#endif //CARDGAME_DRAWTOPCARD_HH
