#ifndef CARDGAME_SANTASE_HH
#define CARDGAME_SANTASE_HH

#include "Command.hh"
#include "Game.h"
#include "SantaseGameInfo.h"

class Santase : public Game {
public:
    Santase();

    bool is_twenty(Card::Suit trump_suit) const {
        std::vector<Card::Suit> suits = SantaseGameInfo().get_suits();
        return std::ranges::any_of(suits, [&](auto suit) {
            return suit != trump_suit && hand_.matching_suits_on_Q_K(suit);
        });
    }

    bool is_fourty(Card::Suit suit) const {
        return hand_.matching_suits_on_Q_K(suit);
    }
};

#endif //CARDGAME_SANTASE_HH
