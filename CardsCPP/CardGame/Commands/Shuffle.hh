#ifndef CARDGAME_SHUFFLE_HH
#define CARDGAME_SHUFFLE_HH

#include "../Command.hh"

template <class Game>
class Shuffle : public Command<Game> {

public:

    const char* get_name() const noexcept override {
        return "shuffle";
    }

    void execute(Game& game) override {
        if (game.is_dealt()) {
            game.clear_hand();
        }
        game.get_deck().shuffle();
        game.get_deck().print();
    }
};

#endif //CARDGAME_SHUFFLE_HH
