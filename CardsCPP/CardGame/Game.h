#ifndef CARDGAME_GAME_H
#define CARDGAME_GAME_H

#include <unordered_map>
#include "Command.hh"
#include "Hand.hh"

class Game {

public:
    virtual ~Game() = 0;

    virtual std::unordered_map<std::string, Command*> get_available_commands() const noexcept = 0;

    virtual Deck& get_deck() = 0;

    virtual Hand& get_hand() = 0;

};

#endif //CARDGAME_GAME_H
