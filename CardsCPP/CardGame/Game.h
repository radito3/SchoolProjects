#ifndef CARDGAME_GAME_H
#define CARDGAME_GAME_H

#include <unordered_map>
#include "Command.hh"
#include "Hand.hh"

class Game {

protected:
    std::unordered_map<std::string, Command*> get_common_commands() const;

    //TODO check whether this way actually eliminates memory leaks
    virtual std::unordered_map<std::string, Command*> build_commands() const = 0;

public:
    virtual ~Game() = 0;

    // TODO the alternative is to clear the memory of the commands in main.cpp
    virtual std::unordered_map<std::string, Command*> get_available_commands() const = 0;

    virtual Deck& get_deck() = 0;

    virtual Hand& get_hand() = 0;

};

#endif //CARDGAME_GAME_H
