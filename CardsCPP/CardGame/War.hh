#ifndef CARDGAME_WAR_HH
#define CARDGAME_WAR_HH

#include "Game.h"

class War : public Game {
    Deck deck_;
    Hand hand_;

    std::unordered_map<std::string, Command *> commands_ = get_available_commands();

public:
    War() : deck_(ranks), hand_(26) {
        deck_.print();
    }

    ~War() override {
        for (const auto& pair : commands_) {
            delete pair.second;
        }
        commands_.clear();
    }

    std::unordered_map<std::string, Command *> get_available_commands() const noexcept override {
        return get_common_commands();
    }

    Deck &get_deck() override {
        return deck_;
    }

    Hand &get_hand() override {
        return hand_;
    }
};

#endif //CARDGAME_WAR_HH
