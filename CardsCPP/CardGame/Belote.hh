#ifndef CARDGAME_BELOTE_HH
#define CARDGAME_BELOTE_HH

#include "Command.hh"
#include "Game.h"
#include <unordered_map>
#include <iostream>
#include <vector>

class Belote : public Game {
    const std::vector<char> belote_ranks = {'7', '8', '9', 'J', 'Q', 'K', 'T', 'A'};

    Deck deck_;
    Hand hand_;

    std::unordered_map<std::string, Command *> get_commands() const;

    bool n_adjacent_cards_of_a_suit(int n) const {
        for (const char suit : suits) {
            if (hand_.adjacent_cards_of_a_suit(suit) >= n) {
                return true;
            }
        }
        return false;
    }

public:
    Belote() : deck_(belote_ranks), hand_(8) {
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

    void print_highest_of_suit(const char suit) const {
        const Card *highest = hand_.get_highest_of_suit(suit);

        if (highest == nullptr) {
            std::cout << std::endl;
        } else {
            std::cout << *highest << std::endl;
        }
    }

    bool is_belote() const {
        for (const char suit : suits) {
            if (hand_.matching_suits_on_Q_K(suit)) {
                return true;
            }
        }
        return false;
    }

    bool is_tierce() const {
        return n_adjacent_cards_of_a_suit(3);
    }

    bool is_quarte() const {
        return n_adjacent_cards_of_a_suit(4);
    }

    bool is_quint() const {
        return n_adjacent_cards_of_a_suit(5);
    }
};

#endif //CARDGAME_BELOTE_HH
