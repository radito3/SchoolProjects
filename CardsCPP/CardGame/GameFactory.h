#ifndef CARDGAME_GAMEFACTORY_H
#define CARDGAME_GAMEFACTORY_H

#include <string_view>
#include <memory>
#include "War.hh"
#include "Belote.hh"
#include "Santase.hh"

class GameFactory {
public:
    GameFactory() = delete;

    static std::unique_ptr<Game> create_game(const std::string_view &name) {
        if (name == "War") {
            return std::make_unique<War>();
        }
        if (name == "Belote") {
            return std::make_unique<Belote>();
        }
        if (name == "Santase") {
            return std::make_unique<Santase>();
        }
        throw GameError("ERROR: Unknown command.");
    }
};

#endif //CARDGAME_GAMEFACTORY_H
