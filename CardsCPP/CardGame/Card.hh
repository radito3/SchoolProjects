#ifndef CARDGAME_CARD_HH
#define CARDGAME_CARD_HH

class Card {
    char suit_;
    char rank_;
    int power_;

public:
    Card(char suit, char rank, int pow)
            : suit_(suit), rank_(rank), power_(pow) {};

    char get_suit() const {
        return suit_;
    }

    char get_rank() const {
        return rank_;
    }

    int get_power() const {
        return power_;
    }
};

bool comp(const Card& a, const Card& b) {
    return a.get_power() < b.get_power();
}

#endif //CARDGAME_CARD_HH
