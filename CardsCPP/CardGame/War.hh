#ifndef CARDGAME_WAR_HH
#define CARDGAME_WAR_HH

#include "Game.h"
#include "WarGameInfo.h"

class War : public Game {
public:
    War() : Game(std::make_unique<WarGameInfo>()) {}
};

#endif //CARDGAME_WAR_HH
