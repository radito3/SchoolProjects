#ifndef CARDGAME_DECK_HH
#define CARDGAME_DECK_HH

#include "Card.hh"
#include "GameError.hh"
#include <deque>
#include <algorithm>
#include <random>
#include <iostream>
#include <vector>

class Deck {
    std::deque<Card> deck_;

    void check_size() const {
        if (deck_.empty()) {
            throw GameError("ERROR: Not enough cards in deck.");
        }
    }

public:
    Deck(const std::vector<char>& suits, const std::vector<char>& ranks) {
        int power = 0;
        for (char suit : suits) {
            for (char rank : ranks) {
                deck_.emplace_back(suit, rank, power++);
            }
        }
    }

    Deck(const Deck &deck) = delete;

    Deck(Deck &&deck) = delete;

    Deck &operator=(const Deck &deck) = delete;

    Deck &operator=(Deck &&deck) = delete;

    void print() const {
        for (const Card &it : deck_) {
            std::cout << it << ' ';
        }
        std::cout << std::endl;
    }

    void shuffle() {
        check_size();
        std::shuffle(deck_.begin(), deck_.end(), std::mt19937(std::random_device()()));
    }

    void sort() {
        check_size();
        std::sort(deck_.begin(), deck_.end(), [](const Card &x, const Card &y) -> bool {
            return x.power < y.power;
        });
    }

    size_t size() const {
        return deck_.size();
    }

    const Card &draw_top_card() {
        const Card &card = get_top_card();
        deck_.pop_back();
        return card;
    }

    const Card &draw_bottom_card() {
        const Card &card = get_bottom_card();
        deck_.pop_front();
        return card;
    }

    const Card &get_top_card() const {
        check_size();
        return deck_.back();
    }

    const Card &get_bottom_card() const {
        check_size();
        return deck_.front();
    }
};

#endif //CARDGAME_DECK_HH
