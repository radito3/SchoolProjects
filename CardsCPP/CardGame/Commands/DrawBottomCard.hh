#ifndef CARDGAME_DRAWBOTTOMCARD_HH
#define CARDGAME_DRAWBOTTOMCARD_HH

#include "../Helpers.hh"
#include "../Command.hh"

template <class T>
class DrawBottomCard : public Command<T> {
    const char* name = nullptr;

public:
    explicit DrawBottomCard(const char* name) {
        this->name = name;
    }

    const char* get_name() const noexcept override {
        return name;
    }

    void execute(T& game_instance) override {
        if (game_instance.is_dealt()) {
            game_instance.clear_hand();
        }
        game_instance.draw_bottom_card();
    }
};

#endif //CARDGAME_DRAWBOTTOMCARD_HH
