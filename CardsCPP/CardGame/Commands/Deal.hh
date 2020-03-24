#ifndef CARDGAME_DEAL_HH
#define CARDGAME_DEAL_HH

#include "../Command.hh"

template <class T>
class Deal : public Command<T> {

public:

    const char* get_name() const noexcept override {
        return "deal";
    }

    void execute(T& game_instance) override {
        game_instance.deal();
//        std::deque<Card> hand = game_instance.get_hand();
        std::cout << game_instance.get_hand() << std::endl;
    }
};

#endif //CARDGAME_DEAL_HH
