#ifndef CARDGAME_GAMEFACTORY_H
#define CARDGAME_GAMEFACTORY_H

#include "War.hh"
#include "Belote.hh"
#include "Santase.hh"

class GameFactory {

public:
    static Game* create_game(const std::string& name) {
        if (name == "War") {
            return new War;
        }
        if (name == "Belote") {
            return new Belote;
        }
        if (name == "Santase") {
            return new Santase;
        }
        throw GameError("ERROR: Unknown command.");
    }

};

#endif //CARDGAME_GAMEFACTORY_H
