#include <ostream>
#include "Card.hh"

std::ostream &operator<<(std::ostream &out, const Card &card) {
    out << card.get_suit();
    if (card.get_rank() == 'T') {
        out << "10";
    } else {
        out << card.get_rank();
    }
    return out;
}
