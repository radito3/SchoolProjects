#ifndef CARDGAME_TOPCARD_HH
#define CARDGAME_TOPCARD_HH

#include <iostream>
#include "../Command.hh"

class TopCard : public Command {
    Game *game_;

public:
    explicit TopCard(Game *game) : game_(game) {}

    bool matches(const std::string &command) override {
        return command == "top_card";
    }

    void execute() override {
        if (game_->get_hand().is_dealt()) {
            game_->get_hand().clear();
        }
        std::cout << game_->get_deck().get_top_card() << std::endl;
    }
};

#endif //CARDGAME_TOPCARD_HH
