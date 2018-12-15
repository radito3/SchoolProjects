#ifndef CARDGAME_WAR_HH
#define CARDGAME_WAR_HH

#include "Hand.hh"

class War : public Hand {

public:
    War() : Hand(26) {
        _create_deck(war_i);
    }
};

inline static std::list<std::shared_ptr<Command<War>>> get_war_commands() {
    return get_common_commands<War>();
}

#endif //CARDGAME_WAR_HH
