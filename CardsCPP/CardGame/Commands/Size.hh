#ifndef CARDGAME_SIZE_HH
#define CARDGAME_SIZE_HH

#include "../Command.hh"

template <class T>
class Size : public Command<T> {
    const char *name = nullptr;

public:
    explicit Size(const char* name) {
        this->name = name;
    }

    const char* get_name() const noexcept override {
        return name;
    }

    void execute(T& game_instance) override {
        if (game_instance.is_dealt()) {
            game_instance.clear_hand();
        }
        std::cout << game_instance.size() << std::endl;
    }
};

#endif //CARDGAME_SIZE_HH
