#ifndef CARDGAME_CARD_HH
#define CARDGAME_CARD_HH

#include <vector>
#include <ostream>
#include <sstream>

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

    std::string to_string() const {
        std::stringstream string_stream;
        string_stream << suit_;
        if (rank_ == 'T') {
            string_stream << "10";
        } else {
            string_stream << rank_;
        }
        return string_stream.str();
    }
};

const char suits[4] = {'C', 'D', 'H', 'S'};
const std::vector<char> ranks = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};

struct card_compare : public std::binary_function<Card *, Card *, bool> {
    bool operator()(const Card *x, const Card *y) const {
        return x->get_power() < y->get_power();
    }
};

#endif //CARDGAME_CARD_HH
