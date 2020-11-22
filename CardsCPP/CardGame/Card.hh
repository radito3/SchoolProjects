#ifndef CARDGAME_CARD_HH
#define CARDGAME_CARD_HH

#include <ostream>

struct Card {
    char suit;
    char rank;
    int power;

    Card(char suit, char rank, int pow)
            : suit(suit), rank(rank), power(pow) {};
};

struct power_comparator {
    bool operator()(const Card *x, const Card *y) const {
        return x->power < y->power;
    }

    bool operator()(const Card &x, const Card &y) const {
        return x.power < y.power;
    }
};

std::ostream &operator<<(std::ostream &, const Card &);

#endif //CARDGAME_CARD_HH
