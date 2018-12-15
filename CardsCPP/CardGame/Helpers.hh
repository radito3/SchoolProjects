#ifndef CARDGAME_HELPERS_HH
#define CARDGAME_HELPERS_HH

#include "Card.hh"
#include "Command.hh"
#include "Commands/TopCard.hh"
#include "Commands/BottomCard.hh"
#include "Commands/DrawBottomCard.hh"
#include "Commands/DrawTopCard.hh"
#include "Commands/IsBelote.hh"
#include "Commands/Shuffle.hh"
#include "Commands/Sort.hh"
#include "Commands/PlayCard.hh"
#include "Commands/Highest.hh"
#include "Commands/Deal.hh"
#include "Commands/Remaining.hh"
#include "Commands/Size.hh"
#include <vector>
#include <ostream>
#include <iomanip>
#include <sstream>
#include <list>
#include <algorithm>
#include <memory>

struct game_info {
    const char suits[4] = { 'C', 'D', 'H', 'S' };
    std::vector<char> ranks;
} war_i, belote_i, santase_i;

inline static void set_game_info() {
    war_i.ranks = { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };
    belote_i.ranks = { '7', '8', '9', 'J', 'Q', 'K', 'T', 'A' };
    santase_i.ranks = { '9', 'J', 'Q', 'K', 'T', 'A' };
}

template <class T>
inline static std::list<std::shared_ptr<Command<T>>> get_common_commands() {
    std::list<std::shared_ptr<Command<T>>> commands;

    commands.push_back(std::make_shared<Size<T>>("size"));
    commands.push_back(std::make_shared<TopCard<T>>("top_card"));
    commands.push_back(std::make_shared<BottomCard<T>>("bottom_card"));
    commands.push_back(std::make_shared<DrawBottomCard<T>>("draw_bottom_card"));
    commands.push_back(std::make_shared<DrawTopCard<T>>("draw_top_card"));
    commands.push_back(std::make_shared<Shuffle<T>>("shuffle"));
    commands.push_back(std::make_shared<Sort<T>>("sort"));
    commands.push_back(std::make_shared<Deal<T>>("deal"));
    commands.push_back(std::make_shared<Remaining<T>>("remaining"));
    commands.push_back(std::make_shared<Highest<T>>("highest"));
    commands.push_back(std::make_shared<PlayCard<T>>("play_card"));

    return commands;
}

static std::vector<std::string> get_input_commands(const char* input) {
    std::vector<std::string> commands;
    std::string segment;
    std::istringstream istr(input);
    while (getline(istr, segment, '.')) {
        commands.push_back(segment);
    }
    return commands;
}

#endif //CARDGAME_HELPERS_HH
