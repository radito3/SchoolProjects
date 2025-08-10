#ifndef CARDGAME_GAME_H
#define CARDGAME_GAME_H

#include <ranges>
#include <span>
#include <memory>
#include <algorithm>
#include "Command.hh"
#include "Deck.hh"
#include "Hand.hh"
#include "GameInfo.h"

class Game {
    std::vector<std::unique_ptr<Command>> commands;

    Command* find_command(const std::string_view& command_name) const {
        auto result = std::ranges::find_if(commands, [&](auto& cmd) { return cmd->matches(command_name); });
        return result != commands.end() ? result->get() : nullptr;
    }

protected:
    Deck deck_;
    Hand hand_;

    void add_command(std::unique_ptr<Command>&& command) {
        commands.push_back(std::move(command));
    }

public:
    explicit Game(std::unique_ptr<GameInfo> game_info);

    Deck& get_deck() {
        return deck_;
    }

    Hand& get_hand() {
        return hand_;
    }

    void play(const std::span<std::string_view>& user_commands) const {
        for (auto& command : user_commands) {
            Command* cmd = find_command(command);
            if (cmd == nullptr) {
                throw GameError("ERROR: Unknown command.");
            }
            cmd->execute();
        }
    }
};

#endif //CARDGAME_GAME_H
