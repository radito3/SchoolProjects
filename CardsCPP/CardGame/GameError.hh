#ifndef CARDGAME_GAMEERROR_HH
#define CARDGAME_GAMEERROR_HH

#include <exception>

class GameError : public std::exception {
    const char* msg_;

public:
    explicit GameError(const char* msg) : msg_(msg) {}

    const char* what() const noexcept override {
        return msg_;
    }
};

#endif //CARDGAME_GAMEERROR_HH
