#ifndef CARDGAME_GAME_H
#define CARDGAME_GAME_H

#include <unordered_map>
#include "Command.hh"
#include "Hand.hh"
#include "Commands.h"

class Game {

protected:
    std::unordered_map<std::string, Command*> get_common_commands() const;

public:
    virtual ~Game() = default;

    virtual Commands get_available_commands() const = 0;

    virtual Deck& get_deck() = 0;

    virtual Hand& get_hand() = 0;

};

#endif //CARDGAME_GAME_H
