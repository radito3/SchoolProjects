#ifndef CARDGAME_TOPCARD_HH
#define CARDGAME_TOPCARD_HH

#include "../Command.hh"

template <class T>
class TopCard : public Command<T> {
    const char* name = nullptr;

public:
    explicit TopCard(const char* name) {
        this->name = name;
    }

    const char* get_name() const noexcept override {
        return name;
    }

    void execute(T& game_instance) override {
        if (game_instance.is_dealt()) {
            game_instance.clear_hand();
        }
        game_instance.top_card();
    }
};

#endif //CARDGAME_TOPCARD_HH
