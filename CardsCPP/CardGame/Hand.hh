#ifndef CARDGAME_HAND_HH
#define CARDGAME_HAND_HH

#include "GameError.hh"
#include "Card.hh"
#include "Deck.hh"
#include "Helpers.hh"
#include <deque>
#include <iostream>

class Hand : public Deck {
     const int hand_size;
     std::deque<Card> hand_;

public:
    explicit Hand(int size) : hand_size(size) {}

    const std::deque<Card>& get_hand() {
        std::sort(hand_.begin(), hand_.end(), comp);
        return hand_;
    }

     bool _matching_suits_on_Q_K(bool match = false, char suit = 'a') {
        const std::deque<Card>& hand = get_hand();

        for (size_t i = 0; i < hand.size() - 1; i++) {
            if (hand.at(i).get_rank() == 'Q' &&
                hand.at(i + 1).get_power() == hand.at(i).get_power() + 1) {
                if (hand_size == 6) { //check if the game is Santase
                    if (match ^ hand.at(i).get_suit() == suit) {
                        return true;
                    }
                    continue;
                }
                return true;
            }
        }
        return false;
    }

     void deal() {
        const std::deque<Card>& deck = get_deck();

        if (deck.size() < hand_size) {
            throw GameError("ERROR: Not enough cards in deck.");
        }

        for (size_t i = deck.size() - 1; i >= hand_size; i--) {
             hand_.push_back(deck.back());
             deck.pop_back();
        }
    }

     bool is_dealt() {
        return !hand_.empty();
    }

     size_t remaining() {
        return hand_.size();
    }

     void clear_hand() {
        hand_.clear();
    }

     void play_card() {
        if (hand_.empty()) {
            throw GameError("ERROR: Not enough cards in hand.");
        }
        std::cout << hand_.back() << std::endl;
        hand_.pop_back();
    }

     void highest() {
        if (hand_.empty()) {
            throw GameError("ERROR: Not enough cards in hand.");
        }
        std::cout << *max_element(hand_.begin(), hand_.end(), comp) << std::endl;
        hand_.erase(max_element(hand_.begin(), hand_.end(), comp));
    }
};

#endif //CARDGAME_HAND_HH
