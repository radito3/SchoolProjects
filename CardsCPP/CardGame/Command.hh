#ifndef CARDGAME_COMMAND_HH
#define CARDGAME_COMMAND_HH

#include <string>

//maybe Operation is a better name?
class Command {

public:
    virtual ~Command() = default;

    //maybe not the best name
    virtual bool matches(const std::string& command) = 0;

    virtual void execute() = 0;

};

#endif //CARDGAME_COMMAND_HH
