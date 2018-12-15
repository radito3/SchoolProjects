#ifndef CARDGAME_REMAINING_HH
#define CARDGAME_REMAINING_HH

#include "../Command.hh"

template <class T>
class Remaining : public Command<T> {
    const char *name = nullptr;

public:
    explicit Remaining(const char* name) {
        this->name = name;
    }

    Remaining(const Remaining& var) = delete;

    const char* get_name() const noexcept override {
        return name;
    }

    void execute(T& game_instance) override {
        if (!game_instance.is_dealt()) {
            throw GameError("ERROR: Unknown command");
        }
        std::cout << game_instance.remaining() << std::endl;
    }
};

#endif //CARDGAME_REMAINING_HH
