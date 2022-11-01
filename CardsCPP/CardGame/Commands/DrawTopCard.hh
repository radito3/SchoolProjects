#ifndef CARDGAME_DRAWTOPCARD_HH
#define CARDGAME_DRAWTOPCARD_HH

#include <iostream>
#include "../Command.hh"

class DrawTopCard : public Command {
    Game *game_;

public:
    explicit DrawTopCard(Game *game) : game_(game) {}

    bool matches(const std::string &command) override {
        return command == "draw_top_card";
    }

    void execute() override {
        if (game_->get_hand().is_dealt()) {
            game_->get_hand().clear();
        }
        std::cout << game_->get_deck().draw_top_card() << std::endl;
    }
};

#endif //CARDGAME_DRAWTOPCARD_HH
