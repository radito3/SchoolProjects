#ifndef CARDGAME_WAR_HH
#define CARDGAME_WAR_HH

#include "Game.h"
#include "WarGameInfo.h"

class War : public Game {
public:
    War() : Game(new WarGameInfo) {}
};

#endif //CARDGAME_WAR_HH
