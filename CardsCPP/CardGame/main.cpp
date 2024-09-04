#include <iostream>
#include <ranges>
#include <algorithm>
#include <string_view>
#include <string>
#include "GameFactory.h"

// compile with: g++-14 --std=c++23 -I$(pwd) -I$(pwd)/Commands *.cpp -o card_game

int main(int argc, char *argv[]) {
    auto input = std::views::split(std::string_view{argv[1]}, '.');
    auto game_name = input | std::views::take(1) | std::views::join | std::ranges::to<std::string>();
    Game *game = nullptr;

    try {
        game = GameFactory::create_game(game_name);
        game->play(input | std::views::drop(1));
    } catch (const GameError &err) {
        std::cerr << err.what() << std::endl;
    }

    delete game;
    return 0;
}
