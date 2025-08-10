#include <memory>
#include "Belote.hh"
#include "Commands/IsBelote.hh"
#include "Commands/IsTierce.h"
#include "Commands/IsQuarte.h"
#include "Commands/IsQuint.h"
#include "Commands/HighestOfSuit.h"

Belote::Belote() : Game(std::make_unique<BeloteGameInfo>()) {
    add_command(std::make_unique<HighestOfSuit>((Belote *) this, Card::Suit::SPADES, "spades"));
    add_command(std::make_unique<HighestOfSuit>((Belote *) this, Card::Suit::HEARTS, "hearts"));
    add_command(std::make_unique<HighestOfSuit>((Belote *) this, Card::Suit::DIAMONDS, "diamonds"));
    add_command(std::make_unique<HighestOfSuit>((Belote *) this, Card::Suit::CLUBS, "clubs"));
    add_command(std::make_unique<IsBelote>((Belote *) this));
    add_command(std::make_unique<IsTierce>((Belote *) this));
    add_command(std::make_unique<IsQuarte>((Belote *) this));
    add_command(std::make_unique<IsQuint>((Belote *) this));
}
