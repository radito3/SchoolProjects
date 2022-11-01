#include "Santase.hh"
#include "Commands/IsFourty.h"
#include "Commands/IsTwenty.h"

Santase::Santase() : Game(new SantaseGameInfo) {
    add_command(new IsFourty((Santase *) this, 'S', "spades"));
    add_command(new IsFourty((Santase *) this, 'H', "hearts"));
    add_command(new IsFourty((Santase *) this, 'D', "diamonds"));
    add_command(new IsFourty((Santase *) this, 'C', "clubs"));
    add_command(new IsTwenty((Santase *) this, 'S', "spades"));
    add_command(new IsTwenty((Santase *) this, 'H', "hearts"));
    add_command(new IsTwenty((Santase *) this, 'D', "diamonds"));
    add_command(new IsTwenty((Santase *) this, 'C', "clubs"));
}
