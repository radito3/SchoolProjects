#ifndef CARDGAME_SANTASE_HH
#define CARDGAME_SANTASE_HH

#include "Command.hh"
#include "Game.h"
#include <bitset>
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

    bool is_twenty(const char suit) {
        size_t pos = 0;
        bool trump_suit = false;
        std::bitset<3> diff_suit;

        for (const char s : suits) {
            bool pair = hand_.matching_suits_on_Q_K(s);
            if (s == suit) {
                trump_suit = pair;
            } else {
                diff_suit.set(pos++, pair);
            }
        }

        return !trump_suit && diff_suit.any();
    }

    bool is_fourty(const char suit) {
        return hand_.matching_suits_on_Q_K(suit);
    }
};

#endif //CARDGAME_SANTASE_HH
