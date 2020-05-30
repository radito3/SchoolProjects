#ifndef CARDGAME_GAMEINFO_H
#define CARDGAME_GAMEINFO_H

#include <vector>

class GameInfo {

public:
    virtual ~GameInfo() = default;

    virtual std::vector<char> get_suits() const = 0;

    virtual std::vector<char> get_ranks() const = 0;

    virtual int get_hand_size() const = 0;
};

#endif //CARDGAME_GAMEINFO_H
