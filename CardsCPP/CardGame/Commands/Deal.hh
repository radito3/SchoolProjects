#ifndef CARDGAME_DEAL_HH
#define CARDGAME_DEAL_HH

#include "../Command.hh"
#include "../Deck.hh"

class Deal : public Command {
    Game *game_;

    struct dealer_impl : public Dealer {
        Deck &deck;

        explicit dealer_impl(Deck &deck) : deck(deck) {}

        size_t num_remaining_cards() override {
            return deck.size();
        }

        Card deal_card() override {
            return deck.draw_top_card();
        }
    };

public:
    explicit Deal(Game *game) : game_(game) {}

    bool matches(const std::string &command) override {
        return command == "deal";
    }

    void execute() override {
        dealer_impl d(game_->get_deck());
        game_->get_hand().deal(&d);
        game_->get_hand().print();
    }
};

#endif //CARDGAME_DEAL_HH
