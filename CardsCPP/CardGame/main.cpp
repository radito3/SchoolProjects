#include <iostream>
#include <vector>
#include <regex>
#include "GameFactory.h"

using namespace std;

int main(int argc, char *argv[]) {
    string input_str(argv[1]);
    string game_name = input_str.substr(0, input_str.find('.'));
    regex re("\\.");
    vector<string> user_commands(++sregex_token_iterator(input_str.begin(), input_str.end(), re, -1),
                                 sregex_token_iterator());
    Game *game = nullptr;

    try {
        game = GameFactory::create_game(game_name);
        game->play(user_commands);
    } catch (const GameError &err) {
        cerr << err.what() << endl;
    }

    delete game;
    return 0;
}
