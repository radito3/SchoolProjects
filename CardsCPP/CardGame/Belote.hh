#ifndef CARDGAME_BELOTE_HH
#define CARDGAME_BELOTE_HH

#include "Hand.hh"
#include "Card.hh"
#include "Helpers.hh"
#include <deque>
#include <iostream>

class Belote : public Hand {

    bool check_suit(size_t current, int depth) {
        std::deque<Card> hand = get_hand();
        int matching = 0;

        for (size_t i = 1; i <= depth; i++) {
            if (hand.at(current).get_suit() == hand.at(current + i).get_suit()) {
                matching++;
            }
        }
        return matching == depth;
    }

    bool check_rank(size_t current_card, size_t current_rank, int depth) {
        std::deque<Card> hand = get_hand();
        int matching = 0;

        for (size_t i = 0; i < depth; ++i) {
            if (hand.at(current_card + i).get_rank() == belote_i.ranks.at(current_rank + i)) {
                matching++;
            }
        }
        return matching == depth;
    }

    bool belote_games(int num1, int num2) {
        std::deque<Card> hand = get_hand();

        for (size_t i = 0; i < hand.size() - num1; i++) {
            if (check_suit(i, num1)) {
                for (size_t j = 0; j < num2; j++) {
                    if (check_rank(i, j, num1)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

public:
    Belote() : Hand(8) {
        _create_deck(belote_i);
    }

    void highest_of_suit(char suit) {
        Card highest(suit, '6', -1);
        const std::deque<Card>& hand = get_hand();

        for (const Card& current : hand) {
            if (current.get_suit() == suit) {
                if (highest.get_power() < current.get_power()) {
                    highest = current;
                }
            }
        }

        if (highest.get_power() == -1) {
            std::cerr << "ERROR: No cards with this suit." << std::endl;
        } else {
            std::cout << highest << std::endl;
        }
    }

    bool is_belote() {
        return _matching_suits_on_Q_K();
    }

    bool is_tierce() {
        return belote_games(2, 6);
    }

    bool is_quarte() {
        return belote_games(3, 5);
    }

    bool is_quint() {
        return belote_games(4, 4);
    }
};

inline static std::list<std::shared_ptr<Command<Belote>>> get_belote_commands() {
    std::list<std::shared_ptr<Command<Belote>>> commands;
    std::list<std::shared_ptr<Command<Belote>>> common = get_common_commands<Belote>();

    commands.insert(commands.cend(), common.cbegin(), common.cend());

    commands.push_back(std::make_shared<IsBelote<Belote>>("belote?"));
    //TODO add remaining commands

    return commands;
}

#endif //CARDGAME_BELOTE_HH
