#include "Belote.hh"
#include "Commands/IsBelote.hh"
#include "Commands/IsTierce.h"
#include "Commands/IsQuarte.h"
#include "Commands/IsQuint.h"
#include "Commands/HighestOfSuit.h"

Belote::Belote() : Game(new BeloteGameInfo) {
    add_command(new HighestOfSuit((Belote *) this, 'S', "spades"));
    add_command(new HighestOfSuit((Belote *) this, 'H', "hearts"));
    add_command(new HighestOfSuit((Belote *) this, 'D', "diamonds"));
    add_command(new HighestOfSuit((Belote *) this, 'C', "clubs"));
    add_command(new IsBelote((Belote *) this));
    add_command(new IsTierce((Belote *) this));
    add_command(new IsQuarte((Belote *) this));
    add_command(new IsQuint((Belote *) this));
}
