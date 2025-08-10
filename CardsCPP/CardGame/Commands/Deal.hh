#ifndef CARDGAME_DEAL_HH
#define CARDGAME_DEAL_HH

#include "../Command.hh"
#include "../Deck.hh"

class Deal : public Command {
    Game *game_;

public:
    explicit Deal(Game *game) : game_(game) {}

    bool matches(const std::string_view &command) override {
        return command == "deal";
    }

    void execute() override {
        game_->get_hand().deal(game_->get_deck().size(), [&]() { return game_->get_deck().draw_top_card(); });
        game_->get_hand().print();
    }
};

#endif //CARDGAME_DEAL_HH
