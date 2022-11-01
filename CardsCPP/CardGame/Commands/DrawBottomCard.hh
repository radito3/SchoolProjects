#ifndef CARDGAME_DRAWBOTTOMCARD_HH
#define CARDGAME_DRAWBOTTOMCARD_HH

#include <iostream>
#include "../Command.hh"

class DrawBottomCard : public Command {
    Game *game_;

public:
    explicit DrawBottomCard(Game *game) : game_(game) {}

    bool matches(const std::string &command) override {
        return command == "draw_bottom_card";
    }

    void execute() override {
        if (game_->get_hand().is_dealt()) {
            game_->get_hand().clear();
        }
        std::cout << game_->get_deck().draw_bottom_card() << std::endl;
    }
};

#endif //CARDGAME_DRAWBOTTOMCARD_HH
