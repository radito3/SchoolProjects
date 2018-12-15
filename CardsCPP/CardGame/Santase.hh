#ifndef CARDGAME_SANTASE_HH
#define CARDGAME_SANTASE_HH

#include "Hand.hh"

class Santase : public Hand {

public:
    Santase() : Hand(6) {
        _create_deck(santase_i);
    }

    bool twenty(char suit) {
        return _matching_suits_on_Q_K(true, suit);
    }

    bool fourty(char suit) {
        return _matching_suits_on_Q_K(false, suit);
    }
};

inline static std::list<std::shared_ptr<Command<Santase>>> get_santase_commands() {
    std::list<std::shared_ptr<Command<Santase>>> commands;
    std::list<std::shared_ptr<Command<Santase>>> common = get_common_commands<Santase>();

    commands.insert(commands.cend(), common.cbegin(), common.cend());

    //TODO add commands for santase

    return commands;
}

#endif //CARDGAME_SANTASE_HH
