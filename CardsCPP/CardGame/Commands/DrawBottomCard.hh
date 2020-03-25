#ifndef CARDGAME_DRAWBOTTOMCARD_HH
#define CARDGAME_DRAWBOTTOMCARD_HH

#include <iostream>
#include "../Command.hh"

class DrawBottomCard : public Command {
    Game* game_;

public:
    explicit DrawBottomCard(Game* game) : game_(game) {}

    ~DrawBottomCard() override = default;

    void execute() override {
        if (game_->get_hand().is_dealt()) {
            game_->get_hand().clear();
        }
        std::cout << game_->get_deck().draw_bottom_card().to_string() << std::endl;
    }
};

#endif //CARDGAME_DRAWBOTTOMCARD_HH
