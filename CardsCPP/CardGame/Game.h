#ifndef CARDGAME_GAME_H
#define CARDGAME_GAME_H

#include <ranges>
#include <algorithm>
#include "Command.hh"
#include "Deck.hh"
#include "Hand.hh"
#include "GameInfo.h"

class Game {
    std::vector<Command*> commands;

    Command* find_command(std::string&& command) const {
        auto result = std::ranges::find_if(commands, [&](auto* cmd) { return cmd->matches(command); });
        return result != commands.end() ? *result : nullptr;
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

    void play(std::ranges::view auto&& user_commands) const {
        for (auto command : user_commands) {  // user_commands is a range of sub-ranges (produced by views::split)
            Command* cmd = find_command(std::string(command.begin(), command.end()));
            if (cmd == nullptr) {
                throw GameError("ERROR: Unknown command.");
            }
            cmd->execute();
        }
    }
};

#endif //CARDGAME_GAME_H
