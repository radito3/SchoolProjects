#ifndef CARDGAME_WARGAMEINFO_H
#define CARDGAME_WARGAMEINFO_H

#include "GameInfo.h"

class WarGameInfo : public GameInfo {

public:
    std::vector<char> get_ranks() const override {
        return {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    }

    int get_hand_size() const override {
        return 26;
    }
};

#endif //CARDGAME_WARGAMEINFO_H
