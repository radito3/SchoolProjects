#include <ostream>
#include "Card.hh"

std::ostream &operator<<(std::ostream &out, const Card &card) {
    out << card.suit;
    if (card.rank == 'T') {
        out << "10";
    } else {
        out << card.rank;
    }
    return out;
}

const char Card::suits[4] = {'C', 'D', 'H', 'S'};

const char Card::ranks[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
