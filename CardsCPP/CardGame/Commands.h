#ifndef CARDGAME_COMMANDS_H
#define CARDGAME_COMMANDS_H

#include "Command.hh"
#include <unordered_map>
#include <utility>

class Commands {
    std::unordered_map<std::string, Command *> commands_;

public:
    explicit Commands(std::unordered_map<std::string, Command *> commands) : commands_(std::move(commands)) {}

    Commands(const Commands &c) = delete;

    Commands(Commands &&commands) noexcept : commands_(std::move(commands.commands_)) {}

    Commands &operator=(const Commands &c) = delete;

    Commands &operator=(Commands &&commands) noexcept {
        commands_ = std::move(commands.commands_);
        return *this;
    }

    ~Commands() {
        for (const auto &pair : commands_) {
            delete pair.second;
        }
        commands_.clear();
    }

    bool is_valid_command(const std::string& command) {
        return commands_.find(command) != commands_.end();
    }

    Command* get_command(const std::string& command) {
        return commands_.find(command)->second;
    }

};

#endif //CARDGAME_COMMANDS_H
