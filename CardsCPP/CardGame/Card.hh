#ifndef CARDGAME_CARD_HH
#define CARDGAME_CARD_HH

#include <vector>
#include <ostream>

const char suits[4] = {'C', 'D', 'H', 'S'};
const std::vector<char> ranks = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};

class Card {
    char suit_;
    char rank_;
    int power_;

public:
    Card(char suit, char rank, int pow)
            : suit_(suit), rank_(rank), power_(pow) {};

    char get_suit() const {
        return suit_;
    }

    char get_rank() const {
        return rank_;
    }

    int get_power() const {
        return power_;
    }
};

std::ostream &operator<<(std::ostream &, const Card &);

#endif //CARDGAME_CARD_HH
