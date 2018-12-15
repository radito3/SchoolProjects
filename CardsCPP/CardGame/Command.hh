#ifndef CARDGAME_COMMAND_HH
#define CARDGAME_COMMAND_HH

#include <cstdint>

template <class T>
class Command {

public:
    virtual const char* get_name() const noexcept = 0;

    virtual void execute(T& var) = 0;

};

#endif //CARDGAME_COMMAND_HH
