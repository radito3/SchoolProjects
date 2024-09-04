#ifndef CARDGAME_BELOTEGAMEINFO_H
#define CARDGAME_BELOTEGAMEINFO_H

#include "GameInfo.h"

class BeloteGameInfo : public GameInfo {

public:
    std::vector<Card::Rank> get_ranks() const override {
        return {Card::Rank::SEVEN, Card::Rank::EIGHT, Card::Rank::NINE,
         Card::Rank::JACK, Card::Rank::QUEEN, Card::Rank::KING, Card::Rank::TEN,
          Card::Rank::ACE};
    }

    int get_hand_size() const override {
        return 8;
    }
};

#endif //CARDGAME_BELOTEGAMEINFO_H
