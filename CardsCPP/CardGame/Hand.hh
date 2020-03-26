#ifndef CARDGAME_HAND_HH
#define CARDGAME_HAND_HH

#include "GameError.hh"
#include "Deck.hh"
#include <set>
#include <algorithm>
#include <iostream>

class Hand {

    struct sort_by_power : public std::binary_function<Card *, Card *, bool> {
        bool operator()(const Card *x, const Card *y) const {
            return x->get_power() < y->get_power();
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

    static int index_of_rank(const char rank) {
        int index = 0;
        for (const char r : ranks) {
            if (r == rank) {
                return index;
            }
            index++;
        }
        return -1;
    }

    struct adjacent_rank_finder : public std::unary_function<Card *, bool> {
        const char rank;

        explicit adjacent_rank_finder(const char rank) : rank(rank) {}

        bool operator()(const Card *card) {
            return (index_of_rank(card->get_rank()) - index_of_rank(rank)) == 1;
        }
    };

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
        Card **temp = new Card *[hand_.size()];

        auto end = std::copy_if(hand_.begin(), hand_.end(), temp, [&](const Card *card) -> bool {
            return card->get_suit() == suit;
        });

        if (temp == end) {
            delete[] temp;
            return 0;
        }

        auto min_by_rank = std::min_element(temp, end, [&](const Card *next, const Card *min) -> bool {
            return index_of_rank(next->get_rank()) < index_of_rank(min->get_rank());
        });

        int num_cards = 1;
        char rank = (*min_by_rank)->get_rank();
        Card **next_of_rank;

        while ((next_of_rank = std::find_if(temp, end, adjacent_rank_finder(rank))) != end) {
            num_cards++;
            rank = (*next_of_rank)->get_rank();
        }

        delete[] temp;
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

        auto highest = *std::max_element(hand_.begin(), hand_.end(),
                                         [&](const Card *largest, const Card *current) -> bool {
                                             return current->get_suit() == suit && sort_by_power()(largest, current);
                                         });
        if (highest->get_suit() != suit) {
            return nullptr;
        }
        return highest;
    }
};

#endif //CARDGAME_HAND_HH
