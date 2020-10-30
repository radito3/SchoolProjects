#include <iostream>
#include <vector>
#include <regex>
#include "GameFactory.h"

using namespace std;

int main(int argc, char *argv[]) {
    string input(argv[1]);
    string game_name = input.substr(0, input.find('.'));
    regex dot("\\.");
    vector<string> user_commands(++sregex_token_iterator(input.begin(), input.end(), dot, -1),
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
