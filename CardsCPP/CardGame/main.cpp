#include <iostream>
#include <unordered_map>
#include <sstream>
#include "GameFactory.h"

using namespace std;

typedef struct input {
    string game_name;
    deque<string> commands;
} input_t;

input_t *parse_input(const char *);
void play(Game *, const deque<string> &);

int main(int argc, char *argv[]) {
    input_t *input = parse_input(argv[1]);
    Game *game = nullptr;

    try {
        game = GameFactory::create_game(input->game_name);
        play(game, input->commands);
    } catch (const GameError &err) {
        cerr << err.what() << endl;
    }

    delete game;
    delete input;

    return 0;
}

input_t *parse_input(const char *input) {
    input_t *res = new input_t;
    deque<string> commands;
    string segment;
    istringstream istr(input);

    while (getline(istr, segment, '.')) {
        commands.push_back(segment);
    }

    res->game_name = *commands.begin();
    commands.pop_front();
    res->commands = commands;

    return res;
}

void play(Game *game, const deque<string> &commands) {
    Commands game_commands = game->get_available_commands();

    for (const string &command : commands) {
        if (!game_commands.is_valid(command)) {
            throw GameError("ERROR: Unknown command.");
        }
        game_commands.get(command)->execute();
    }
}
