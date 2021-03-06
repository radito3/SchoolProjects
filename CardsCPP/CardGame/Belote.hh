#ifndef CARDGAME_BELOTE_HH
#define CARDGAME_BELOTE_HH

#include "Command.hh"
#include "Game.h"
#include "BeloteGameInfo.h"
#include <unordered_map>
#include <iostream>
#include <vector>

class Belote : public Game {

    std::unordered_map<std::string, Command *> get_commands() const;

    bool n_adjacent_cards_of_a_suit(int n) const {
        std::vector<char> suits = BeloteGameInfo().get_suits();
        return std::any_of(suits.begin(), suits.end(), [&](const char& suit) -> bool {
            return hand_.adjacent_cards_of_a_suit(suit) >= n;
        });
    }

public:
    Belote() : Game(new BeloteGameInfo) {}

    Commands get_available_commands() const override {
        return Commands(get_commands());
    }

    void print_highest_of_suit(const char& suit) const {
        const Card *highest = hand_.get_highest_of_suit(suit);

        if (highest == nullptr) {
            std::cout << std::endl;
        } else {
            std::cout << *highest << std::endl;
        }
    }

    bool is_belote() const {
        std::vector<char> suits = BeloteGameInfo().get_suits();
        return std::any_of(suits.begin(), suits.end(), [&](const char& suit) -> bool {
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
