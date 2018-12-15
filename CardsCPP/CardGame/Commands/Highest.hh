#ifndef CARDGAME_HIGHEST_HH
#define CARDGAME_HIGHEST_HH

#include "../Command.hh"

template <class T>
class Highest : public Command<T> {
    const char *name = nullptr;

public:
    explicit Highest(const char* name) {
        this->name = name;
    }

    const char* get_name() const noexcept override {
        return name;
    }

    void execute(T& game_instance) override {
        if (!game_instance.is_dealt()) {
            throw GameError("ERROR: Unknown command");
        }
        game_instance.highest();
    }
};

#endif //CARDGAME_HIGHEST_HH
