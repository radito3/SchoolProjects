#ifndef CARDGAME_SANTASE_HH
#define CARDGAME_SANTASE_HH

#include "Command.hh"
#include "Game.h"
#include "SantaseGameInfo.h"
#include <unordered_map>

class Santase : public Game {

    std::unordered_map<std::string, Command *> get_commands() const;

public:
    Santase() : Game(new SantaseGameInfo) {}

    Commands get_available_commands() const override {
        return Commands(get_commands());
    }

    bool is_twenty(const char trump_suit) const {
        std::vector<char> suits = SantaseGameInfo().get_suits();
        return std::any_of(suits.begin(), suits.end(), [&](const char& suit) -> bool {
            return suit != trump_suit && hand_.matching_suits_on_Q_K(suit);
        });
    }

    bool is_fourty(const char suit) const {
        return hand_.matching_suits_on_Q_K(suit);
    }
};

#endif //CARDGAME_SANTASE_HH
