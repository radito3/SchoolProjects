#include "Santase.hh"
#include "Commands/IsFourty.h"
#include "Commands/IsTwenty.h"

Santase::Santase() : Game(std::make_unique<SantaseGameInfo>()) {
    add_command(std::make_unique<IsFourty>((Santase *) this, Card::Suit::SPADES, "spades"));
    add_command(std::make_unique<IsFourty>((Santase *) this, Card::Suit::HEARTS, "hearts"));
    add_command(std::make_unique<IsFourty>((Santase *) this, Card::Suit::DIAMONDS, "diamonds"));
    add_command(std::make_unique<IsFourty>((Santase *) this, Card::Suit::CLUBS, "clubs"));
    add_command(std::make_unique<IsTwenty>((Santase *) this, Card::Suit::SPADES, "spades"));
    add_command(std::make_unique<IsTwenty>((Santase *) this, Card::Suit::HEARTS, "hearts"));
    add_command(std::make_unique<IsTwenty>((Santase *) this, Card::Suit::DIAMONDS, "diamonds"));
    add_command(std::make_unique<IsTwenty>((Santase *) this, Card::Suit::CLUBS, "clubs"));
}
