#ifndef CARDGAME_GAMEINFO_H
#define CARDGAME_GAMEINFO_H

#include <vector>

class GameInfo {

public:
    virtual ~GameInfo() = default;

    virtual std::vector<Card::Suit> get_suits() const {
        return {Card::Suit::CLUBS, Card::Suit::DIAMONDS, Card::Suit::HEARTS, Card::Suit::SPADES};
    }

    virtual std::vector<Card::Rank> get_ranks() const = 0;

    virtual int get_hand_size() const = 0;
};

#endif //CARDGAME_GAMEINFO_H
