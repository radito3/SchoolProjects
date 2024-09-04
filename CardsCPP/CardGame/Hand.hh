#ifndef CARDGAME_HAND_HH
#define CARDGAME_HAND_HH

#include "GameError.hh"
#include "Dealer.h"
#include <set>
#include <ranges>
#include <algorithm>
#include <iostream>

class Hand {

    std::set<Card, power_comparator> hand_;
    const int hand_size_;
    bool dealt_;

    void check_size() const {
        if (hand_.empty()) {
            throw GameError("ERROR: Not enough cards in hand.");
        }
    }

    int create_bitfield_from_hand(Card::Suit suit) const {
        int result = 0;
        for (auto& card : hand_) {
            if (card.suit == suit) {
                result |= (1 << static_cast<int>(card.rank));
            }
        }
        return result;
    }

public:
    explicit Hand(int hand_size) : hand_size_(hand_size), dealt_(false) {}

    Hand(const Hand &hand) = delete;

    Hand(Hand &&hand) = delete;

    Hand &operator=(const Hand &hand) = delete;

    Hand &operator=(Hand &&hand) = delete;

    ~Hand() {
        clear();
    }

    bool matching_suits_on_Q_K(char suit) const {
        auto matching = std::ranges::count_if(hand_, [&](const Card &card) {
            return card.suit == suit && (card.rank == Card::Rank::QUEEN || card.rank == Card::Rank::KING);
        });
        return matching == 2;
    }

    int adjacent_cards_of_a_suit(Card::Suit suit) const {
        int bitfield = create_bitfield_from_hand(suit);
        int max_sequence = 0;  // longest consecutive bit subsequence

        while (bitfield != 0) {
            bitfield &= (bitfield << 1);  // Collapse consecutive 1s
            max_sequence++;
        }

        return max_sequence;
    }

    void deal(Dealer* dealer) {
        if (dealer->num_remaining_cards() < hand_size_) {
            throw GameError("ERROR: Not enough cards in deck.");
        }
        for (size_t i = 0; i < hand_size_; i++) {
            hand_.insert(dealer->deal_card());
        }
        dealt_ = true;
    }

    void print() const {
        for (auto& it : hand_) {
            std::cout << it << ' ';
        }
        std::cout << std::endl;
    }

    bool is_dealt() const {
        return dealt_;
    }

    size_t size() const {
        return hand_.size();
    }

    void clear() {
        dealt_ = false;
        hand_.clear();
    }

    Card draw_first() {
        check_size();
        Card first = *hand_.begin();
        hand_.erase(hand_.begin());
        return first;
    }

    Card draw_highest() {
        check_size();
        Card last = *--hand_.end();
        hand_.erase(--hand_.end());
        return last;
    }

    Card get_highest_of_suit(Card::Suit suit) const {
        check_size();
        auto highest = std::ranges::find_if(std::ranges::reverse_view{hand_}, [&](auto& card) {
            return card.suit == suit;
        });

        if (highest == std::ranges::rend(hand_)) {
            return {};
        }
        return *highest;
    }
};

#endif //CARDGAME_HAND_HH
