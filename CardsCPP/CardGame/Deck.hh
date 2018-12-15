#ifndef CARDGAME_DECK_HH
#define CARDGAME_DECK_HH

#include "Card.hh"
#include "Helpers.hh"
#include "GameError.hh"
#include <deque>
#include <algorithm>
#include <random>
#include <iostream>

class Deck {
     std::deque<Card> deck_;

public:

     void _create_deck(game_info info) {
        int power = 0;
        for (char i : info.suits) {
            for (char j : info.ranks) {
                Card a(i, j, power++);
                deck_.push_back(a);
            }
        }
    }

     void _erase(const std::deque<Card>::const_iterator& begin, const std::deque<Card>::const_iterator& end) {
        deck_.erase(begin, end);
    }

     const std::deque<Card>& get_deck() const {
        return deck_;
    }

     void shuffle_deck() {
        if (deck_.empty()) {
            throw GameError("ERROR: Not enough cards in deck.");
        }
        std::shuffle(deck_.begin(), deck_.end(), std::mt19937(std::random_device()()));
        std::cout << deck_ << std::endl;
    }

     size_t size() {
        return deck_.size();
    }

     void draw_top_card() {
        top_card();
        deck_.pop_back();
    }

     void draw_bottom_card() {
        bottom_card();
        deck_.pop_front();
    }

     void top_card() {
        if (deck_.empty()) {
            throw GameError("ERROR: Not enough cards in deck.");
        }
        std::cout << deck_.back() << std::endl;
    }

     void bottom_card() {
        if (deck_.empty()) {
            throw GameError("ERROR: Not enough cards in deck.");
        }
        std::cout << deck_.front() << std::endl;
    }
};

#endif //CARDGAME_DECK_HH
