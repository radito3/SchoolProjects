#ifndef CARDGAME_HAND_HH
#define CARDGAME_HAND_HH

#include "GameError.hh"
#include "Deck.hh"
#include <set>
#include <algorithm>

class Hand {
    const int hand_size_;
    std::set<Card, card_compare> hand_;
    bool is_dealt_;

public:
    explicit Hand(int size) : hand_size_(size), is_dealt_(false) {}

    Hand(const Hand& hand) = delete;

    ~Hand() {
        hand_.clear();
    }

    bool _matching_suits_on_Q_K(const char suit) {
        int matching = std::count_if(hand_.begin(), hand_.end(), [&](const Card& card) -> bool {
            return card.get_suit() == suit && (card.get_rank() == 'Q' || card.get_rank() == 'K');
        });
        return matching == 2;
    }

    int adjacent_cards_of_a_suit(const char suit) {
        auto first_of_a_suit = std::find_if(hand_.begin(), hand_.end(), [&](const Card& card) -> bool {
            return card.get_suit() == suit;
        });

        if (first_of_a_suit == hand_.end()) {
            return 0;
        }

        int pow = first_of_a_suit->get_power(), num_cards = 1;

        for (const Card& card : hand_) {
            if (card.get_power() == (pow + 1)) {
                pow++;
                num_cards++;
            }
        }
        return num_cards;
    }

    void deal(Deck& deck) {
        if (deck.size() < hand_size_) {
            throw GameError("ERROR: Not enough cards in deck.");
        }
        for (size_t i = 0; i < hand_size_; i++) {
            hand_.insert(deck.draw_top_card());
        }
        is_dealt_ = true;
    }

    bool is_dealt() const {
        return is_dealt_;
    }

    size_t remaining() const {
        return hand_.size();
    }

    void clear() {
        is_dealt_ = false;
        hand_.clear();
    }

    const Card& play_card() {
        if (hand_.empty()) {
            throw GameError("ERROR: Not enough cards in hand.");
        }
        return *hand_.begin();
    }

    const Card& get_highest() {
        if (hand_.empty()) {
            throw GameError("ERROR: Not enough cards in hand.");
        }
        return *--hand_.end();
    }

    const Card* get_highest_of_suit(char suit) {
        if (hand_.empty()) {
            throw GameError("ERROR: Not enough cards in hand.");
        }

        if (std::none_of(hand_.begin(), hand_.end(), [&](const Card& card) -> bool {
            return card.get_suit() == suit;
        })) {
            return nullptr;
        }

        auto highest = std::max_element(hand_.begin(), hand_.end(), [&](const Card& largest, const Card& current) -> bool {
            return current.get_suit() == suit && card_compare()(largest, current);
        });

        return &(*highest);
    }
};

#endif //CARDGAME_HAND_HH
