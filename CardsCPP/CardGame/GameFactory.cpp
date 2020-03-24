#include "GameFactory.h"

#include "War.hh"
#include "Belote.hh"
#include "Santase.hh"

Game* GameFactory::create_game(const std::string& name) {
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
