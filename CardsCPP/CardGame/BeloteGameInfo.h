#ifndef CARDGAME_BELOTEGAMEINFO_H
#define CARDGAME_BELOTEGAMEINFO_H

#include "GameInfo.h"

class BeloteGameInfo : public GameInfo {

public:
    std::vector<char> get_suits() const override {
        return {'C', 'D', 'H', 'S'};
    }

    std::vector<char> get_ranks() const override {
        return {'7', '8', '9', 'J', 'Q', 'K', 'T', 'A'};
    }

    int get_hand_size() const override {
        return 8;
    }
};

#endif //CARDGAME_BELOTEGAMEINFO_H
