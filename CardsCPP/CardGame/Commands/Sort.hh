#ifndef CARDGAME_SORT_HH
#define CARDGAME_SORT_HH

#include <deque>
#include <algorithm>
#include "../Command.hh"
#include "../Card.hh"
#include "../OperatorOverloading.hh"

template <class Game>
class Sort : public Command<Game> {

public:

    const char* get_name() const noexcept override {
        return "sort";
    }

    void execute(Game& game) override {
        if (game.get_hand().is_dealt()) {
            game.get_hand().clear();
        }
        game.get_deck().sort();
        game.get_deck().print();
    }
};

#endif //CARDGAME_SORT_HH
