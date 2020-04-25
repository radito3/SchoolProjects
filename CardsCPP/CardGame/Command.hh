#ifndef CARDGAME_COMMAND_HH
#define CARDGAME_COMMAND_HH

//maybe Operation is a better name?
class Command {

public:
    virtual ~Command() = default;

    virtual void execute() = 0;

};

#endif //CARDGAME_COMMAND_HH
