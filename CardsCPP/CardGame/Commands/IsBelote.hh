#ifndef CARDGAME_ISBELOTE_HH
#define CARDGAME_ISBELOTE_HH

#include <iostream>
#include "../Command.hh"
#include "../GameError.hh"

class IsBelote : public Command {
    Belote* game_;

public:
    explicit IsBelote(Belote* game) : game_(game) {}

    ~IsBelote() override = default;

    void execute() override {
        if (!game_->get_hand().is_dealt()) {
            throw GameError("ERROR: Unknown command.");
        }
        std::cout << std::boolalpha << game_->is_belote() << std::noboolalpha << std::endl;
    }
};

#endif //CARDGAME_ISBELOTE_HH
