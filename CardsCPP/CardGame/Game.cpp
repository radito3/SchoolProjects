#include "Game.h"

#include "Commands/Size.hh"
#include "Commands/TopCard.hh"
#include "Commands/BottomCard.hh"
#include "Commands/DrawBottomCard.hh"
#include "Commands/Highest.hh"
#include "Commands/PlayCard.hh"
#include "Commands/Deal.hh"
#include "Commands/Remaining.hh"
#include "Commands/Sort.hh"
#include "Commands/DrawTopCard.hh"
#include "Commands/Shuffle.hh"

Game::Game(GameInfo *game_info)
        : deck_(game_info->get_suits(), game_info->get_ranks()), hand_(game_info->get_hand_size()) {
    deck_.print();
    delete game_info;
    add_command(new Size((Game *) this));
    add_command(new TopCard((Game *) this));
    add_command(new BottomCard((Game *) this));
    add_command(new DrawBottomCard((Game *) this));
    add_command(new DrawTopCard((Game *) this));
    add_command(new Shuffle((Game *) this));
    add_command(new Sort((Game *) this));
    add_command(new Deal((Game *) this));
    add_command(new Remaining((Game *) this));
    add_command(new Highest((Game *) this));
    add_command(new PlayCard((Game *) this));
}
