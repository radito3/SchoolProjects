#include <iostream>
#include <unordered_map>
#include "GameFactory.h"

using namespace std;

vector<string> get_input_commands(const char *);

void play(Game *, const vector<string> &);

int main(int argc, char *argv[]) {
    vector<string> commands = get_input_commands(argv[1]);

    Game* game = nullptr;
    try {
        game = GameFactory::create_game(commands[0]);
        play(game, commands);
    } catch (const GameError &err) {
        cerr << err.what() << endl;
    }
    delete game;

    return 0;
}

vector<string> get_input_commands(const char *input) {
    vector<string> commands;
    string segment;
    istringstream string_stream(input);
    while (getline(string_stream, segment, '.')) {
        commands.push_back(segment);
    }
    return commands;
}

void play(Game *game, const vector<string> &commands) {
    unordered_map<string, Command *> game_commands = game->get_available_commands();

    for (size_t i = 1; i < commands.size(); i++) {
        string command = commands[i];
        auto game_command = game_commands.find(command);

        if (game_command == game_commands.end()) {
            throw GameError("ERROR: Unknown command.");
        }
        game_command->second->execute();
    }
}
