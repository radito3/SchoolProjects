#ifndef CARDGAME_BELOTE_HH
#define CARDGAME_BELOTE_HH

#include "Hand.hh"
#include "Card.hh"
#include "Command.hh"
#include "Game.h"
#include <unordered_map>
#include <iostream>
#include <vector>

class Belote : public Game {
    const std::vector<char> belote_ranks = {'7', '8', '9', 'J', 'Q', 'K', 'T', 'A' };

    Deck deck_;
    Hand hand_;

    std::unordered_map<std::string, Command *> commands_ = get_available_commands();

    bool n_adjacent_cards_of_a_suit(int n) {
        for (const char suit : suits) {
            if (hand_.adjacent_cards_of_a_suit(suit) == n) {
                return true;
            }
        }
        return false;
    }

public:
    Belote() : deck_(belote_ranks), hand_(8) {
        deck_.print();
    }

    ~Belote() override {
        for (const auto& pair : commands_) {
            delete pair.second;
        }
        commands_.clear();
    }

    std::unordered_map<std::string, Command *> get_available_commands() const noexcept override;

    Deck &get_deck() override {
        return deck_;
    }

    Hand &get_hand() override {
        return hand_;
    }

    void print_highest_of_suit(char suit) {
        const Card* highest = hand_.get_highest_of_suit(suit);

        if (highest == nullptr) {
            std::cout << std::endl;
        } else {
            std::cout << highest->to_string() << std::endl;
        }
    }

    bool is_belote() {
        for (const char suit : suits) {
            if (hand_.matching_suits_on_Q_K(suit)) {
                return true;
            }
        }
        return false;
    }

    bool is_tierce() {
        return n_adjacent_cards_of_a_suit(3);
    }

    bool is_quarte() {
        return n_adjacent_cards_of_a_suit(4);
    }

    bool is_quint() {
        return n_adjacent_cards_of_a_suit(5);
    }
};

#endif //CARDGAME_BELOTE_HH
