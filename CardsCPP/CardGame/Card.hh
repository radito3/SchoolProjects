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

std::ostream &operator<<(std::ostream &, const Card &);

#endif //CARDGAME_CARD_HH
