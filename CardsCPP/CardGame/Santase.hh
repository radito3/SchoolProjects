#ifndef CARDGAME_SANTASE_HH
#define CARDGAME_SANTASE_HH

#include "Command.hh"
#include "Game.h"
#include <unordered_map>

class Santase : public Game {
    const std::vector<char> santase_ranks = {'9', 'J', 'Q', 'K', 'T', 'A'};

    Deck deck_;
    Hand hand_;

    std::unordered_map<std::string, Command *> get_commands() const;

public:
    Santase() : deck_(santase_ranks), hand_(6) {
        deck_.print();
    }

    Commands get_available_commands() const override {
        return Commands(get_commands());
    }

    Deck &get_deck() override {
        return deck_;
    }

    Hand &get_hand() override {
        return hand_;
    }

    bool is_twenty(const char trump_suit) {
        for (const char suit : suits) {
            if (suit != trump_suit && hand_.matching_suits_on_Q_K(suit)) {
                return true;
            }
        }
        return false;
    }

    bool is_fourty(const char suit) {
        return hand_.matching_suits_on_Q_K(suit);
    }
};

#endif //CARDGAME_SANTASE_HH
