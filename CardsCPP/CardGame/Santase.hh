#ifndef CARDGAME_SANTASE_HH
#define CARDGAME_SANTASE_HH

#include "Hand.hh"
#include <algorithm>
#include <bitset>

class Santase : public Game {
    const std::vector<char> santase_ranks = {'9', 'J', 'Q', 'K', 'T', 'A' };

    Deck deck_;
    Hand hand_;

    std::unordered_map<std::string, Command *> commands_ = get_available_commands();

public:
    Santase() : deck_(santase_ranks), hand_(6) {
        deck_.print();
    }

    ~Santase() override {
        for (const auto& pair : commands_) {
            delete pair.second;
        }
        commands_.clear();
    }

    //TODO move to source file
    std::unordered_map<std::string, Command*> get_available_commands() const noexcept override {
        std::unordered_map<std::string, Command*> commands = get_common_commands();

        //TODO add santase commands

        return commands;
    }

    Deck& get_deck() override {
        return deck_;
    }

    Hand& get_hand() override {
        return hand_;
    }

    bool twenty(char suit) {
        size_t pos = 0;
        bool same_suit = false;
        std::bitset<3> diff_suit;

        for (const char s : suits) {
            bool matching_suits_on_Q_K = hand_.matching_suits_on_Q_K(suit);
            if (s == suit) {
                same_suit = matching_suits_on_Q_K;
            } else {
                diff_suit.set(pos++, matching_suits_on_Q_K);
            }
        }

        return !same_suit && diff_suit.any();
    }

    bool fourty(char suit) {
        return hand_.matching_suits_on_Q_K(suit);
    }
};

#endif //CARDGAME_SANTASE_HH
