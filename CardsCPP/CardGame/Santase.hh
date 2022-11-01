#ifndef CARDGAME_SANTASE_HH
#define CARDGAME_SANTASE_HH

#include "Command.hh"
#include "Game.h"
#include "SantaseGameInfo.h"

class Santase : public Game {
public:
    Santase();

    bool is_twenty(char trump_suit) const {
        std::vector<char> suits = SantaseGameInfo().get_suits();
        return std::any_of(suits.cbegin(), suits.cend(), [&](char suit) -> bool {
            return suit != trump_suit && hand_.matching_suits_on_Q_K(suit);
        });
    }

    bool is_fourty(char suit) const {
        return hand_.matching_suits_on_Q_K(suit);
    }
};

#endif //CARDGAME_SANTASE_HH
