#ifndef CARDGAME_WAR_HH
#define CARDGAME_WAR_HH

#include "Game.h"

class War : public Game {
    Deck deck_;
    Hand hand_;

public:
    War() : deck_(ranks), hand_(26) {
        deck_.print();
    }

    ~War() override = default;

    Commands get_available_commands() const override {
        return Commands(get_common_commands());
    }

    Deck &get_deck() override {
        return deck_;
    }

    Hand &get_hand() override {
        return hand_;
    }
};

#endif //CARDGAME_WAR_HH
