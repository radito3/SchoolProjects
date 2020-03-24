#ifndef CARDGAME_OPERATOROVERLOADING_HH
#define CARDGAME_OPERATOROVERLOADING_HH

#include <ostream>
#include <list>
#include "Card.hh"

std::ostream& operator<<(std::ostream& out, const Card& d) {
    out << d.get_suit();
    if (d.get_rank() == 'T') {
        out << "10";
    } else {
        out << d.get_rank();
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const std::list<Card>& d) {
    for (const Card& it : d) {
        out << it << " ";
    }
    return out;
}

#endif //CARDGAME_OPERATOROVERLOADING_HH
