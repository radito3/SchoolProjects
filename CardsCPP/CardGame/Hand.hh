#ifndef CARDGAME_HAND_HH
#define CARDGAME_HAND_HH

#include "GameError.hh"
#include "Deck.hh"
#include <set>
#include <algorithm>
#include <iostream>

class Hand {

    struct sort_by_power {
        bool operator()(const Card *x, const Card *y) const {
            return x->power < y->power;
        }
    };

    struct sort_by_rank {
        bool operator()(const Card *x, const Card *y) const {
            return index_of_rank(x) < index_of_rank(y);
        }
    };

    std::set<Card *, sort_by_power> hand_;
    const int hand_size_;
    bool dealt_;

    void check_size() const {
        if (hand_.empty()) {
            throw GameError("ERROR: Not enough cards in hand.");
        }
    }

    static int index_of_rank(const Card* card) {
        std::string ranks_str(Card::ranks);
        return ranks_str.find(card->rank);
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
            return card->suit == suit && (card->rank == 'Q' || card->rank == 'K');
        });
        return matching == 2;
    }

    int adjacent_cards_of_a_suit(const char suit) const {
        std::set<Card *, sort_by_rank> temp;

        std::copy_if(hand_.begin(), hand_.end(), std::inserter(temp, temp.begin()), [&](const Card *card) -> bool {
            return card->suit == suit;
        });

        if (temp.empty()) {
            return 0;
        }

        int num_cards = 1;
        bool found_adjacent = false;

        for (auto it = ++temp.begin(); it != temp.end(); it++, it++) {
            if ((index_of_rank(*it) - index_of_rank(*--it)) == 1) {
                num_cards++;
                found_adjacent = true;
            } else if (found_adjacent) {
                num_cards = 1;
                found_adjacent = false;
            }
        }

        return num_cards;
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

    const Card *get_highest_of_suit(const char suit) const {
        check_size();

        auto highest = *std::max_element(hand_.begin(), hand_.end(),
                                         [&](const Card *largest, const Card *current) -> bool {
                                             return current->suit == suit && sort_by_power()(largest, current);
                                         });
        if (highest->suit != suit) {
            return nullptr;
        }
        return highest;
    }
};

#endif //CARDGAME_HAND_HH
