#ifndef CARDGAME_GAME_H
#define CARDGAME_GAME_H

#include "Command.hh"
#include "Deck.hh"
#include "Hand.hh"
#include "GameInfo.h"

class Game {
    std::vector<Command*> commands;

    Command* find_command(const std::string& command) const {
        for (auto* cmd : commands) {
            if (cmd->matches(command)) {
                return cmd;
            }
        }
        return nullptr;
    }

protected:
    Deck deck_;
    Hand hand_;

    void add_command(Command* command) {
        commands.push_back(command);
    }

public:
    explicit Game(GameInfo* game_info);

    virtual ~Game() {
        for (auto* cmd : commands) {
            delete cmd;
        }
    }

    Deck& get_deck() {
        return deck_;
    }

    Hand& get_hand() {
        return hand_;
    }

    void play(const std::vector<std::string>& user_commands) const {
        for (const std::string& command : user_commands) {
            Command* cmd = find_command(command);
            if (cmd == nullptr) {
                throw GameError("ERROR: Unknown command.");
            }
            cmd->execute();
        }
    }
};

#endif //CARDGAME_GAME_H
