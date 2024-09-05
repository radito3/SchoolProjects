#ifndef CARDGAME_CARD_HH
#define CARDGAME_CARD_HH

#include <ostream>

struct Card {
    
    enum Suit {
        CLUBS, DIAMONDS, HEARTS, SPADES
    };

    enum Rank {
        TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE
    };

    Suit suit;
    Rank rank;
    int power;

    Card(Suit suit, Rank rank, int pow)
            : suit(suit), rank(rank), power(pow) {};

    Card() : suit(Suit::CLUBS), rank(Rank::TWO), power(-1) {}
};

struct power_comparator {
    bool operator()(const Card &x, const Card &y) const {
        return x.power < y.power;
    }
};

struct rank_comparator {
    bool operator()(const Card &x, const Card &y) const {
        return static_cast<int>(x.rank) < static_cast<int>(y.rank);
    }
};

std::ostream &operator<<(std::ostream &, const Card &);

std::ostream &operator<<(std::ostream &, const Card::Suit &);

std::ostream &operator<<(std::ostream &, const Card::Rank &);

#endif //CARDGAME_CARD_HH
