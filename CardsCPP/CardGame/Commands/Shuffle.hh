#ifndef CARDGAME_SHUFFLE_HH
#define CARDGAME_SHUFFLE_HH

#include "../Command.hh"

template <class T>
class Shuffle : public Command<T> {
    const char* name = nullptr;

public:
    explicit Shuffle(const char* name) {
        this->name = name;
    }

    const char* get_name() const noexcept override {
        return name;
    }

    void execute(T& game_instance) override {
        if (game_instance.is_dealt()) {
            game_instance.clear_hand();
        }
        game_instance.shuffle_deck();
    }
};

#endif //CARDGAME_SHUFFLE_HH
