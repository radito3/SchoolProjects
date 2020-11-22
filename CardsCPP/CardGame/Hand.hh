#ifndef CARDGAME_HAND_HH
#define CARDGAME_HAND_HH

#include "GameError.hh"
#include "Deck.hh"
#include <set>
#include <algorithm>
#include <iostream>

class Hand {

    struct rank_comparator {
        const std::string ranks = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};

        bool operator()(const Card *x, const Card *y) const {
            return ranks.find(x->rank) < ranks.find(y->rank);
        }
    } rank_cmp;

    std::set<Card *, power_comparator> hand_;
    const int hand_size_;
    bool dealt_;

    void check_size() const {
        if (hand_.empty()) {
            throw GameError("ERROR: Not enough cards in hand.");
        }
    }

    int index_of_rank(const Card* card) const {
        return rank_cmp.ranks.find(card->rank);
    }

public:
    explicit Hand(int hand_size) : hand_size_(hand_size), dealt_(false) {}

    Hand(const Hand &hand) = delete;

    Hand(Hand &&deck) = delete;

    Hand &operator=(const Hand &deck) = delete;

    Hand &operator=(Hand &&deck) = delete;

    ~Hand() {
        clear();
    }

    bool matching_suits_on_Q_K(const char suit) const {
        int matching = std::count_if(hand_.begin(), hand_.end(), [&](const Card *card) -> bool {
            return card->suit == suit && (card->rank == 'Q' || card->rank == 'K');
        });
        return matching == 2;
    }

    int adjacent_cards_of_a_suit(const char suit) const {
        std::set<Card *, rank_comparator> cards_by_rank;

        for (auto* card : hand_) {
            if (card->suit == suit) {
                cards_by_rank.insert(card);
            }
        }

        if (cards_by_rank.empty()) {
            return 0;
        }

        int current_sequence = 1, max_sequence = 1;
        auto current = cards_by_rank.begin();
        auto next = current;
        ++next;

        for (; next != cards_by_rank.end(); ++current, ++next) {
            if ((index_of_rank(*next) - index_of_rank(*current)) == 1) {
                current_sequence++;
            } else {
                current_sequence = 1;
            }

            if (current_sequence > max_sequence) {
                max_sequence = current_sequence;
            }
        }
        return max_sequence;
    }

    void deal(Deck &deck) {
        if (deck.size() < hand_size_) {
            throw GameError("ERROR: Not enough cards in deck.");
        }
        for (size_t i = 0; i < hand_size_; i++) {
            hand_.insert(new Card(deck.draw_top_card()));
        }
        dealt_ = true;
    }

    void print() const {
        for (const Card *it : hand_) {
            std::cout << *it << ' ';
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
        for (const Card *card : hand_) {
            delete card;
        }
    }

    const Card *draw_first() {
        check_size();
        const Card *first = *hand_.begin();
        hand_.erase(hand_.begin());
        return first;
    }

    const Card *draw_highest() {
        check_size();
        const Card *last = *--hand_.end();
        hand_.erase(--hand_.end());
        return last;
    }

    const Card *get_highest_of_suit(const char& suit) const {
        check_size();
        auto highest = std::find_if(hand_.rbegin(), hand_.rend(), [&](const Card* card) {
            return card->suit == suit;
        });

        if (highest == hand_.rend()) {
            return nullptr;
        }
        return *highest;
    }
};

#endif //CARDGAME_HAND_HH
