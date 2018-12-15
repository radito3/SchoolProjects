#ifndef CARDGAME_ISBELOTE_HH
#define CARDGAME_ISBELOTE_HH

#include <iostream>
#include <string>
#include "../Command.hh"
#include "../GameError.hh"

template <class T>
class IsBelote : public Command<T> {
    const char* name = nullptr;

public:
    explicit IsBelote(const char* name) {
        this->name = name;
    }

    const char* get_name() const noexcept override {
        return name;
    }

    void execute(T& game_instance) override {
        if (!game_instance.is_dealt()) {
            throw GameError("ERROR: Unknown command.");
        }
        std::cout << game_instance.is_belote() << std::endl;
    }

};

#endif //CARDGAME_ISBELOTE_HH
