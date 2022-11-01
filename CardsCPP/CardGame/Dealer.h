#ifndef CARDGAME_DEALER_H
#define CARDGAME_DEALER_H

#include "Card.hh"

class Dealer {
public:
    virtual size_t num_remaining_cards() = 0;

    virtual Card deal_card() = 0;
};

#endif //CARDGAME_DEALER_H
