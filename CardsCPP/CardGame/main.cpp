#include <iostream>
#include <unordered_map>
#include <sstream>
#include "GameFactory.h"

using namespace std;

vector<string> get_input_commands(const char *);
void play(Game *, const vector<string> &);

int main(int argc, char *argv[]) {
    //TODO validate input
    vector<string> commands = get_input_commands(argv[1]);

    cout << boolalpha;
    try {
        Game *game = GameFactory::create_game(commands[0]);

        play(game, commands);

        delete game;
    } catch (const GameError &err) {
        cerr << err.what() << endl;
    }
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
    for (size_t i = 1; i < commands.size(); i++) {
        string command = commands[i];
        unordered_map<string, Command *> game_commands = game->get_available_commands();
        auto game_command = game_commands.find(command);

        if (game_command == game_commands.end()) {
            throw GameError("ERROR: Unknown command.");
        }
        game_command->second->execute();
    }
}
