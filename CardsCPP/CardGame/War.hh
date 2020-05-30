#ifndef CARDGAME_WAR_HH
#define CARDGAME_WAR_HH

#include "Game.h"
#include "WarGameInfo.h"

class War : public Game {

public:
    War() : Game(new WarGameInfo) {}

    Commands get_available_commands() const override {
        return Commands(get_common_commands());
    }
};

#endif //CARDGAME_WAR_HH
