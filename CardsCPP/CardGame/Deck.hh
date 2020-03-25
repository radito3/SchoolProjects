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

public:
    explicit Deck(const std::vector<char> &game_ranks) {
        int power = 0;
        for (char i : suits) {
            for (char j : game_ranks) {
                deck_.emplace_back(i, j, power++);
            }
        }
    }

    Deck(const Deck &deck) = delete;

    Deck(Deck &&deck) = delete;

    Deck &operator=(const Deck &deck) = delete;

    Deck &operator=(Deck &&deck) = delete;

    ~Deck() {
        deck_.clear();
    }

    void print() const {
        for (const Card &it : deck_) {
            std::cout << it.to_string() << " ";
        }
        std::cout << std::endl;
    }

    void shuffle() {
        if (deck_.empty()) {
            throw GameError("ERROR: Not enough cards in deck.");
        }
        std::shuffle(deck_.begin(), deck_.end(), std::mt19937(std::random_device()()));
    }

    void sort() {
        if (deck_.empty()) {
            throw GameError("ERROR: Not enough cards in deck.");
        }
        std::sort(deck_.begin(), deck_.end(), [&](const Card& x, const Card& y) -> bool {
            return x.get_power() < y.get_power();
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
        if (deck_.empty()) {
            throw GameError("ERROR: Not enough cards in deck.");
        }
        return deck_.back();
    }

    const Card &get_bottom_card() const {
        if (deck_.empty()) {
            throw GameError("ERROR: Not enough cards in deck.");
        }
        return deck_.front();
    }
};

#endif //CARDGAME_DECK_HH
