#include "Belote.hh"
#include "Commands/IsBelote.hh"
#include "Commands/IsTierce.h"
#include "Commands/IsQuarte.h"
#include "Commands/IsQuint.h"
#include "Commands/HighestOfSuit.h"

Belote::Belote() : Game(new BeloteGameInfo) {
    add_command(new HighestOfSuit((Belote *) this, Card::Suit::SPADES, "spades"));
    add_command(new HighestOfSuit((Belote *) this, Card::Suit::HEARTS, "hearts"));
    add_command(new HighestOfSuit((Belote *) this, Card::Suit::DIAMONDS, "diamonds"));
    add_command(new HighestOfSuit((Belote *) this, Card::Suit::CLUBS, "clubs"));
    add_command(new IsBelote((Belote *) this));
    add_command(new IsTierce((Belote *) this));
    add_command(new IsQuarte((Belote *) this));
    add_command(new IsQuint((Belote *) this));
}
