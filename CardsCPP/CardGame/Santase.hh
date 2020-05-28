#ifndef CARDGAME_SANTASE_HH
#define CARDGAME_SANTASE_HH

#include "Command.hh"
#include "Game.h"
#include <unordered_map>

class Santase : public Game {
    static const char santase_ranks[];

    std::unordered_map<std::string, Command *> get_commands() const;

public:
    Santase() : Game(santase_ranks, 6) {}

    Commands get_available_commands() const override {
        return Commands(get_commands());
    }

    bool is_twenty(const char trump_suit) const {
        for (const char suit : Card::suits) {
            if (suit != trump_suit && hand_.matching_suits_on_Q_K(suit)) {
                return true;
            }
        }
        return false;
    }

    bool is_fourty(const char suit) const {
        return hand_.matching_suits_on_Q_K(suit);
    }
};

#endif //CARDGAME_SANTASE_HH
