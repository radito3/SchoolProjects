#ifndef CARDGAME_SIZE_HH
#define CARDGAME_SIZE_HH

#include <iostream>
#include "../Command.hh"

class Size : public Command {
    Game *game_;

public:
    explicit Size(Game *game) : game_(game) {}

    bool matches(const std::string &command) override {
        return command == "size";
    }

    void execute() override {
        if (game_->get_hand().is_dealt()) {
            game_->get_hand().clear();
        }
        std::cout << game_->get_deck().size() << std::endl;
    }
};

#endif //CARDGAME_SIZE_HH
