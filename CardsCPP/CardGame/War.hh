#ifndef CARDGAME_WAR_HH
#define CARDGAME_WAR_HH

#include "Game.h"
#include "Commands/Size.hh"
#include "Commands/Size.hh"

class War : public Game {
    Deck deck_;
    Hand hand_;

public:
    War() : deck_(ranks), hand_(26) {
        deck_.print();
    }

    ~War() override {
        //TODO free dynamically allocated commands
    }

    //TODO the commands should be a private map so that they can be garbage collected in the destructor
    std::unordered_map<std::string, Command*> get_available_commands() const noexcept override {
        std::unordered_map<std::string, Command*> commands;

        commands.insert({"size", new Size((Game*) this)});

//        commands.push_back(std::make_shared<TopCard>("top_card"));
//        commands.push_back(std::make_shared<BottomCard>("bottom_card"));
//        commands.push_back(std::make_shared<DrawBottomCard>("draw_bottom_card"));
//        commands.push_back(std::make_shared<DrawTopCard>("draw_top_card"));
//        commands.push_back(std::make_shared<Shuffle>("shuffle"));
//        commands.push_back(std::make_shared<Sort>("sort"));
//        commands.push_back(std::make_shared<Deal>("deal"));
//        commands.push_back(std::make_shared<Remaining>("remaining"));
//        commands.push_back(std::make_shared<Highest>("highest"));
//        commands.push_back(std::make_shared<PlayCard>("play_card"));

        return commands;
    }

    Deck& get_deck() override {
        return deck_;
    }

    Hand& get_hand() override {
        return hand_;
    }
};

#endif //CARDGAME_WAR_HH
