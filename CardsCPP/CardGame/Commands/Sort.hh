#ifndef CARDGAME_SORT_HH
#define CARDGAME_SORT_HH

#include <deque>
#include <algorithm>
#include "../Command.hh"
#include "../Card.hh"
#include "../OperatorOverloading.hh"

template <class T>
class Sort : public Command<T> {
    const char* name = nullptr;

public:
    explicit Sort(const char* name) {
        this->name = name;
    }

    const char* get_name() const noexcept override {
        return name;
    }

    void execute(T& game_instance) override {
        if (game_instance.is_dealt()) {
            game_instance.clear_hand();
        }
        std::deque<Card> deck = game_instance.get_deck();
        std::sort(deck.begin(), deck.end(), comp);
        std::cout << deck << std::endl;
    }
};

#endif //CARDGAME_SORT_HH
