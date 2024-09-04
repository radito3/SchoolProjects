#ifndef CARDGAME_BELOTE_HH
#define CARDGAME_BELOTE_HH

#include "Command.hh"
#include "Game.h"
#include "BeloteGameInfo.h"
#include <iostream>
#include <vector>

class Belote : public Game {

    bool n_adjacent_cards_of_a_suit(int n) const {
        std::vector<Card::Suit> suits = BeloteGameInfo().get_suits();
        return std::ranges::any_of(suits, [&](auto suit) {
            return hand_.adjacent_cards_of_a_suit(suit) >= n;
        });
    }

public:
    Belote();

    void print_highest_of_suit(Card::Suit suit) const {
        Card highest = hand_.get_highest_of_suit(suit);

        if (highest.power == -1) {
            std::cout << std::endl;
        } else {
            std::cout << highest << std::endl;
        }
    }

    bool is_belote() const {
        std::vector<Card::Suit> suits = BeloteGameInfo().get_suits();
        return std::ranges::any_of(suits, [&](auto suit) {
            return hand_.matching_suits_on_Q_K(suit);
        });
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
