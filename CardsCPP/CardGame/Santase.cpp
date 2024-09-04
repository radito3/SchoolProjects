#include "Santase.hh"
#include "Commands/IsFourty.h"
#include "Commands/IsTwenty.h"

Santase::Santase() : Game(new SantaseGameInfo) {
    add_command(new IsFourty((Santase *) this, Card::Suit::SPADES, "spades"));
    add_command(new IsFourty((Santase *) this, Card::Suit::HEARTS, "hearts"));
    add_command(new IsFourty((Santase *) this, Card::Suit::DIAMONDS, "diamonds"));
    add_command(new IsFourty((Santase *) this, Card::Suit::CLUBS, "clubs"));
    add_command(new IsTwenty((Santase *) this, Card::Suit::SPADES, "spades"));
    add_command(new IsTwenty((Santase *) this, Card::Suit::HEARTS, "hearts"));
    add_command(new IsTwenty((Santase *) this, Card::Suit::DIAMONDS, "diamonds"));
    add_command(new IsTwenty((Santase *) this, Card::Suit::CLUBS, "clubs"));
}
