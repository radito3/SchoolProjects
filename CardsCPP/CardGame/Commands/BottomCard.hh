#ifndef CARDGAME_BOTTOMCARD_HH
#define CARDGAME_BOTTOMCARD_HH

#include "../Command.hh"

template <class T>
class BottomCard : public Command<T> {
    const char* name = nullptr;

public:
    BottomCard(const char* name) : name(name) {
//        this->name = name;
    }

    const char* get_name() const noexcept override {
        return name;
    }

    void execute(T& game_instance) override {
        if (game_instance.is_dealt()) {
            game_instance.clear_hand();
        }
        game_instance.bottom_card();
    }
};

#endif //CARDGAME_BOTTOMCARD_HH
