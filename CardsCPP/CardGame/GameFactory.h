#ifndef CARDGAME_GAMEFACTORY_H
#define CARDGAME_GAMEFACTORY_H

#include "Game.h"

class GameFactory {

public:
    static Game* create_game(const std::string& name);

};

#endif //CARDGAME_GAMEFACTORY_H
