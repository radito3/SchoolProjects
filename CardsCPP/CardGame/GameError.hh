#ifndef CARDGAME_GAMEERROR_HH
#define CARDGAME_GAMEERROR_HH

#include <stdexcept>

class GameError : public std::runtime_error {
public:
    explicit GameError(const char* message) : runtime_error(message) {}
};

#endif //CARDGAME_GAMEERROR_HH
