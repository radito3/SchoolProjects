#ifndef CARDGAME_DRAWTOPCARD_HH
#define CARDGAME_DRAWTOPCARD_HH

#include "../Command.hh"

template <class T>
class DrawTopCard : public Command<T> {
    const char* name = nullptr;

public:
    explicit DrawTopCard(const char* name) {
        this->name = name;
    }

    const char* get_name() const noexcept override {
        return name;
    }

    void execute(T& game_instance) override {
        if (game_instance.is_dealt()) {
            game_instance.clear_hand();
        }
        game_instance.draw_top_card();
    }
};

#endif //CARDGAME_DRAWTOPCARD_HH
