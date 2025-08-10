#include <iostream>
#include <ranges>
#include <string_view>
#include <span>
#include "GameFactory.h"

// compile with: g++ --std=c++23 -Wall -Wpedantic -I$(pwd) -I$(pwd)/Commands *.cpp -o card_game
int main(int argc, char *argv[]) {
    std::vector<std::string_view> parts;
    for (auto part : std::string_view{argv[1]} | std::views::split('.')) {
        parts.emplace_back(&*part.begin(), std::ranges::distance(part));
    }

    auto game_name = parts[0];
    auto args = std::span(parts.begin() + 1, parts.end());
    try {
        auto game = GameFactory::create_game(game_name);
        game->play(args);
    } catch (const GameError &err) {
        std::cerr << err.what() << std::endl;
    }
    return 0;
}
