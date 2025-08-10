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

Game::Game(std::unique_ptr<GameInfo> game_info)
        : deck_(game_info->get_suits(), game_info->get_ranks()), hand_(game_info->get_hand_size()) {
    deck_.print();
    add_command(std::make_unique<Size>((Game *) this));
    add_command(std::make_unique<TopCard>((Game *) this));
    add_command(std::make_unique<BottomCard>((Game *) this));
    add_command(std::make_unique<DrawBottomCard>((Game *) this));
    add_command(std::make_unique<DrawTopCard>((Game *) this));
    add_command(std::make_unique<Shuffle>((Game *) this));
    add_command(std::make_unique<Sort>((Game *) this));
    add_command(std::make_unique<Deal>((Game *) this));
    add_command(std::make_unique<Remaining>((Game *) this));
    add_command(std::make_unique<Highest>((Game *) this));
    add_command(std::make_unique<PlayCard>((Game *) this));
}
