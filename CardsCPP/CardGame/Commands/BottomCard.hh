#ifndef CARDGAME_BOTTOMCARD_HH
#define CARDGAME_BOTTOMCARD_HH

#include <iostream>
#include "../Command.hh"

class BottomCard : public Command {
    Game *game_;

public:
    explicit BottomCard(Game *game) : game_(game) {}

    bool matches(const std::string &command) override {
        return command == "bottom_card";
    }

    void execute() override {
        if (game_->get_hand().is_dealt()) {
            game_->get_hand().clear();
        }
        std::cout << game_->get_deck().get_bottom_card() << std::endl;
    }
};

#endif //CARDGAME_BOTTOMCARD_HH
