#ifndef CARDGAME_HAND_HH
#define CARDGAME_HAND_HH

#include "GameError.hh"
#include "Deck.hh"
#include <set>
#include <algorithm>
#include <iostream>

class Hand {
    const int hand_size_;
    std::set<Card *, sort_by_power> hand_;
    bool dealt_;

    void check_size() const {
        if (hand_.empty()) {
            throw GameError("ERROR: Not enough cards in hand.");
        }
    }

    struct sort_by_rank : public std::binary_function<Card *, Card *, bool> {
        bool operator()(const Card *x, const Card *y) const {
            return get_index_of_rank(x->get_rank()) < get_index_of_rank(y->get_rank());
        }
    };

    static long get_index_of_rank(const char rank) {
        return std::distance(ranks.begin(), std::find(ranks.begin(), ranks.end(), rank));
    }

public:
    explicit Hand(int size) : hand_size_(size), dealt_(false) {}

    Hand(const Hand &hand) = delete;

    Hand(Hand &&deck) = delete;

    Hand &operator=(const Hand &deck) = delete;

    Hand &operator=(Hand &&deck) = delete;

    ~Hand() {
        clear();
    }

    bool matching_suits_on_Q_K(const char suit) const {
        int matching = std::count_if(hand_.begin(), hand_.end(), [&](const Card *card) -> bool {
            return card->get_suit() == suit && (card->get_rank() == 'Q' || card->get_rank() == 'K');
        });
        return matching == 2;
    }

    int adjacent_cards_of_a_suit(const char suit) const {
        std::set<Card *, sort_by_rank> temp(hand_.begin(), hand_.end());

        return std::count_if(temp.begin(), temp.end(), [&](const Card *card) -> bool {
            return card->get_suit() == suit;
        });
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
            std::cout << it->to_string() << " ";
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
        hand_.clear();
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

    const Card *get_highest_of_suit(char suit) const {
        check_size();

        if (std::none_of(hand_.begin(), hand_.end(), [&](const Card *card) -> bool {
            return card->get_suit() == suit;
        })) {
            return nullptr;
        }

        return *std::max_element(hand_.begin(), hand_.end(),
                                 [&](const Card *largest, const Card *current) -> bool {
                                     return current->get_suit() == suit && sort_by_power()(largest, current);
                                 });
    }
};

#endif //CARDGAME_HAND_HH
