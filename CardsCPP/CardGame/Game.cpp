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

std::unordered_map<std::string, Command *> Game::get_common_commands() const {
    std::unordered_map<std::string, Command *> commands;

    commands.emplace("size", new Size((Game *) this));
    commands.emplace("top_card", new TopCard((Game *) this));
    commands.emplace("bottom_card", new BottomCard((Game *) this));
    commands.emplace("draw_bottom_card", new DrawBottomCard((Game *) this));
    commands.emplace("draw_top_card", new DrawTopCard((Game *) this));
    commands.emplace("shuffle", new Shuffle((Game *) this));
    commands.emplace("sort", new Sort((Game *) this));
    commands.emplace("deal", new Deal((Game *) this));
    commands.emplace("remaining", new Remaining((Game *) this));
    commands.emplace("highest", new Highest((Game *) this));
    commands.emplace("play_card", new PlayCard((Game *) this));

    return commands;
}
