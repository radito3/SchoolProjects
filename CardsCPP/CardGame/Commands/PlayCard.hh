#ifndef CARDGAME_PLAYCARD_HH
#define CARDGAME_PLAYCARD_HH

#include "../Command.hh"

template <class T>
class PlayCard : public Command<T> {
    const char *name = nullptr;

public:
    explicit PlayCard(const char* name) {
        this->name = name;
    }

    const char* get_name() const noexcept override {
        return name;
    }

    void execute(T& game_instance) override {
        if (!game_instance.is_dealt()) {
            throw GameError("ERROR: Unknown command");
        }
        game_instance.play_card();
    }
};

#endif //CARDGAME_PLAYCARD_HH
