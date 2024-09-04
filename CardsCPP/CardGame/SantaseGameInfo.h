#ifndef CARDGAME_SANTASEGAMEINFO_H
#define CARDGAME_SANTASEGAMEINFO_H

#include "GameInfo.h"

class SantaseGameInfo : public GameInfo {

public:
    std::vector<Card::Rank> get_ranks() const override {
        return {Card::Rank::NINE, Card::Rank::JACK, Card::Rank::QUEEN,
         Card::Rank::KING, Card::Rank::TEN, Card::Rank::ACE};
    }

    int get_hand_size() const override {
        return 6;
    }
};

#endif //CARDGAME_SANTASEGAMEINFO_H
