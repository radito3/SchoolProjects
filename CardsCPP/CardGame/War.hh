#ifndef CARDGAME_WAR_HH
#define CARDGAME_WAR_HH

#include "Game.h"

class War : public Game {

public:
    War() : Game(Card::ranks, 26) {}

    Commands get_available_commands() const override {
        return Commands(get_common_commands());
    }
};

#endif //CARDGAME_WAR_HH
