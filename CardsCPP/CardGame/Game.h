#ifndef CARDGAME_GAME_H
#define CARDGAME_GAME_H

#include <unordered_map>
#include "Command.hh"
#include "Hand.hh"
#include "Commands.h"

class Game {

protected:
    std::unordered_map<std::string, Command*> get_common_commands() const;

    Deck deck_;
    Hand hand_;

public:
    Game(const char game_ranks[], int hand_size) : deck_(game_ranks), hand_(hand_size) {
        deck_.print();
    }

    virtual ~Game() = default;

    virtual Commands get_available_commands() const = 0;

    Deck& get_deck() {
        return deck_;
    }

    Hand& get_hand() {
        return hand_;
    }

    void play(const std::vector<std::string>& user_commands) const {
        Commands game_commands = get_available_commands();

        for (const std::string& command : user_commands) {
            if (!game_commands.is_valid(command)) {
                throw GameError("ERROR: Unknown command.");
            }
            game_commands.get(command)->execute();
        }
    }
};

#endif //CARDGAME_GAME_H
