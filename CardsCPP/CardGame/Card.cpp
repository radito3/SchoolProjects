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
