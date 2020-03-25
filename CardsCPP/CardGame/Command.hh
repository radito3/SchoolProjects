#ifndef CARDGAME_COMMAND_HH
#define CARDGAME_COMMAND_HH

//TODO maybe Operation is a better name
class Command {

public:
    //A constructor with a Game* protected field could be made.
    //That way, for Santase and Belote specific commands the game
    //field would be used via dynamic_cast<>()

    virtual ~Command() = 0;

    virtual void execute() = 0;

};

#endif //CARDGAME_COMMAND_HH
