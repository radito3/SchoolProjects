#include <iostream>
#include <memory>
#include "War.hh"
#include "Belote.hh"
#include "Santase.hh"

using namespace std;

template <class T>
static void play(T game, const list<shared_ptr<Command<T>>>& available_commands, const vector<string>& commands) {
    cout << game.get_deck() << endl;
    for (size_t i = 1; i < commands.size(); i++) {
        for (const shared_ptr<Command<T>>& c : available_commands) {
            if (c->get_name() == commands.at(i)) {
                c->execute(game);
                break;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    set_game_info();
    vector<string> commands = get_input_commands(argv[1]);

    cout << boolalpha;
    try {
        if (commands[0] == "War") {
            War game;
            list<shared_ptr<Command<War>>> available_commands = get_war_commands();
            play(game, available_commands, commands);
        } else if (commands[0] == "Belote") {
            Belote game;
            list<shared_ptr<Command<Belote>>> available_commands = get_belote_commands();
            play(game, available_commands, commands);
        } else if (commands[0] == "Santase") {
            Santase game;
            list<shared_ptr<Command<Santase>>> available_commands = get_santase_commands();
            play(game, available_commands, commands);
        } else {
            throw GameError("ERROR: Unknown command.");
        }
    } catch(const GameError& err) {
        cerr << err.what() << endl;
    }

    return 0;
}
