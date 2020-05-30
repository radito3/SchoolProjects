#ifndef CARDGAME_SANTASEGAMEINFO_H
#define CARDGAME_SANTASEGAMEINFO_H

#include "GameInfo.h"

class SantaseGameInfo : public GameInfo {

public:
    std::vector<char> get_ranks() const override {
        return {'9', 'J', 'Q', 'K', 'T', 'A'};
    }

    int get_hand_size() const override {
        return 6;
    }
};

#endif //CARDGAME_SANTASEGAMEINFO_H
