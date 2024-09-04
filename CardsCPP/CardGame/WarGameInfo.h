#ifndef CARDGAME_WARGAMEINFO_H
#define CARDGAME_WARGAMEINFO_H

#include "GameInfo.h"

class WarGameInfo : public GameInfo {

public:
    std::vector<Card::Rank> get_ranks() const override {
        return {Card::Rank::TWO, Card::Rank::THREE, Card::Rank::FOUR, Card::Rank::FIVE,
         Card::Rank::SIX, Card::Rank::SEVEN, Card::Rank::EIGHT, Card::Rank::NINE, Card::Rank::TEN,
          Card::Rank::JACK, Card::Rank::QUEEN, Card::Rank::KING, Card::Rank::ACE};
    }

    int get_hand_size() const override {
        return 26;
    }
};

#endif //CARDGAME_WARGAMEINFO_H
