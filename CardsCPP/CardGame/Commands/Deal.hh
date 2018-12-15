#ifndef CARDGAME_DEAL_HH
#define CARDGAME_DEAL_HH

#include "../Command.hh"

template <class T>
class Deal : public Command<T> {
    const char *name = nullptr;

public:
    explicit Deal(const char* name) {
        this->name = name;
    }

    const char* get_name() const noexcept override {
        return name;
    }

    void execute(T& game_instance) override {
        game_instance.deal();
//        std::deque<Card> hand = game_instance.get_hand();
        std::cout << game_instance.get_hand() << std::endl;
    }
};

#endif //CARDGAME_DEAL_HH
