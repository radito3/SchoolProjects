#include <iostream>
#include <algorithm>
#include <random>
#include <sstream>

using namespace std;

class GameError : public exception {
    const char* msg_;

public:
    explicit GameError(const char* msg) : msg_(msg) {}

    const char* what() const noexcept override {
        return msg_;
    }
};

struct game_info {
    const char suits[4] = { 'C', 'D', 'H', 'S' };
    vector<char> ranks;
} war_i, belote_i, santase_i;

const static inline void set_game_info() {
    war_i.ranks = { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };
    belote_i.ranks = { '7', '8', '9', 'J', 'Q', 'K', 'T', 'A' };
    santase_i.ranks = { '9', 'J', 'Q', 'K', 'T', 'A' };
}

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

ostream& operator<<(ostream& out, Card d) {
    out << d.get_suit();
    if (d.get_rank() == 'T') {
        out << "10";
    } else {
        out << d.get_rank();
    }
    return out;
}

ostream& operator<<(ostream& out, const vector<Card>& d) {
    for (const Card &it : d) {
        out << it << " ";
    }
    return out;
}

bool comp(Card a, Card b) {
    return a.get_power() < b.get_power();
}

class Deck {
    vector<Card> deck_;

public:

    void _create_deck(game_info info) {
        int power = 0;
        for (char i : info.suits) {
            for (char j : info.ranks) {
                Card a(i, j, power++);
                deck_.push_back(a);
            }
        }
    }

    void _erase(vector<Card>::const_iterator begin, vector<Card>::const_iterator end) {
        deck_.erase(begin, end);
    }

    vector<Card> get_deck() const {
        return deck_;
    }

    void shuffle_deck() {
        if (deck_.empty()) {
            throw GameError("ERROR: Not enough cards in deck.");
        }
        shuffle(deck_.begin(), deck_.end(), mt19937(random_device()()));
        cout << deck_ << endl;
    }

    size_t size() const {
        return deck_.size();
    }

    void draw_top_card() {
        top_card();
        deck_.pop_back();
    }

    void draw_bottom_card() {
        bottom_card();
        deck_.erase(deck_.begin());
    }

    void top_card() {
        if (deck_.empty()) {
            throw GameError("ERROR: Not enough cards in deck.");
        }
        cout << deck_.back() << endl;
    }

    void bottom_card() {
        if (deck_.empty()) {
            throw GameError("ERROR: Not enough cards in deck.");
        }
        cout << deck_.front() << endl;
    }
};

class Hand : public Deck {
    const int hand_size;
    vector<Card> hand_;

public:
    explicit Hand(int size) : hand_size(size) {}

    vector<Card> get_hand() {
        sort(hand_.begin(), hand_.end(), comp);
        return hand_;
    }

    bool _matching_suits_on_Q_K(bool match = false, char suit = 'a') {
        vector<Card> hand = get_hand();

        for (int i = 0; i < hand.size() - 1; i++) {
            if (hand[i].get_rank() == 'Q' &&
                    hand[i + 1].get_power() == hand[i].get_power() + 1) {
                if (hand_size == 6) { //check if the game is Santase
                    if (match ^ hand[i].get_suit() == suit) {
                        return true;
                    }
                    continue;
                }
                return true;
            }
        }
        return false;
    }

    void deal() {
        vector<Card> deck = get_deck();

        if (deck.size() < hand_size) {
            throw GameError("ERROR: Not enough cards in deck.");
        }

        reverse(deck.begin(), deck.end());
        for (int i = 0; i < hand_size; i++) {
            hand_.push_back(deck[i]);
        }
        _erase(deck.begin(), deck.begin() + hand_size);
        reverse(deck.begin(), deck.end());
    }

    size_t remaining() const {
        return hand_.size();
    }

    void play_card() {
        if (hand_.empty()) {
            throw GameError("ERROR: Not enough cards in hand.");
        }
        cout << hand_.back() << endl;
        hand_.pop_back();
    }

    void highest() {
        if (hand_.empty()) {
            throw GameError("ERROR: Not enough cards in hand.");
        }
        cout << *max_element(hand_.begin(), hand_.end(), comp) << endl;
        hand_.erase(max_element(hand_.begin(), hand_.end(), comp));
    }
};

class War : public Hand {

public:
    War() : Hand(26) {
        _create_deck(war_i);
    }
};

class Belote : public Hand {

    bool check_suit(size_t current, int depth) {
        vector<Card> hand = get_hand();
        int matching = 0;

        for (size_t i = 1; i <= depth; i++) {
            if (hand.at(current).get_suit() == hand.at(current + i).get_suit()) {
                matching++;
            }
        }
        return matching == depth;
    }

    bool check_rank(size_t current_card, size_t current_rank, int depth) {
        vector<Card> hand = get_hand();
        int matching = 0;

        for (size_t i = 0; i < depth; ++i) {
            if (hand.at(current_card + i).get_rank() == belote_i.ranks.at(current_rank + i)) {
                matching++;
            }
        }
        return matching == depth;
    }

    bool belote_games(int num1, int num2) {
        vector<Card> hand = get_hand();

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
        vector<Card> hand = get_hand();

        for (Card current : hand) {
            if (current.get_suit() == suit) {
                if (highest.get_power() < current.get_power()) {
                    highest = current;
                }
            }
        }

        if (highest.get_power() == -1) {
            cerr << "ERROR: No cards with this suit." << endl;
        } else {
            cout << highest << endl;
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

class Santase : public Hand {

public:
    Santase() : Hand(6) {
        _create_deck(santase_i);
    }

    bool twenty(char suit) {
        return _matching_suits_on_Q_K(true, suit);
    }

    bool fourty(char suit) {
        return _matching_suits_on_Q_K(false, suit);
    }
};

template <class T>
bool common_commands(const string& command, T& game, vector<Card>& hand, bool& dealt, vector<Card>& deck) {
    if (command == "size") {
        if (dealt == true) { hand.clear(); dealt = false; }
        cout << game.size() << endl;
    } else if (command == "draw_top_card") {
        if (dealt == true) { hand.clear(); dealt = false; }
        game.draw_top_card();
    } else if (command == "draw_bottom_card") {
        if (dealt == true) { hand.clear(); dealt = false; }
        game.draw_bottom_card();
    } else if (command == "top_card") {
        if (dealt == true) { hand.clear(); dealt = false; }
        game.top_card();
    } else if (command == "bottom_card") {
        if (dealt == true) { hand.clear(); dealt = false; }
        game.bottom_card();
    } else if (command == "shuffle") {
        if (dealt == true) { hand.clear(); dealt = false; }
        game.shuffle_deck();
    } else if (command == "sort") {
        if (dealt == true) { hand.clear(); dealt = false; }
        sort(deck.begin(), deck.end(), comp);
        cout << deck << endl;
    } else if (command == "deal") {
        game.deal();
        if (dealt == false) dealt = true;
        hand = game.get_hand();
        cout << hand << endl;
    } else if (command == "remaining") {
        if (dealt == false) throw GameError("ERROR: Unknown command.");
        cout << game.remaining() << endl;
    } else if (command == "play_card") {
        if (dealt == false) throw GameError("ERROR: Unknown command.");
        game.play_card();
    } else if (command == "highest") {
        if (dealt == false) throw GameError("ERROR: Unknown command.");
        game.highest();
    } else {
	    return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    set_game_info();

    vector<string> commands;
    string segment;
    istringstream istr(argv[1]);
    while (getline(istr, segment, '.')) {
        commands.push_back(segment);
    }

    vector<Card> deck, hand;
    bool dealt = false;
    cout << boolalpha;
    try {
        if (commands[0] == "War") {
            War game;
            deck = game.get_deck();
            cout << deck << endl;
            for (size_t i = 1; i < commands.size(); i++) {
                if (!common_commands<War>(commands[i], game, hand, dealt, deck)) {
		            throw GameError("ERROR: Unknown command.");
		        }
            }
        } else if (commands[0] == "Belote") {
            Belote game;
            deck = game.get_deck();
            cout << deck << endl;
            for (size_t i = 1; i < commands.size(); i++) {
                if (common_commands<Belote>(commands[i], game, hand, dealt, deck)) {
                    //
                } else if (commands[i] == "tierce?") {
                    if (dealt == false) throw GameError("ERROR: Unknown command.");
                    cout << game.is_tierce() << endl;
                } else if (commands[i] == "belote?") {
                    if (dealt == false) throw GameError("ERROR: Unknown command.");
                    cout << game.is_belote() << endl;
                } else if (commands[i] == "quarte?") {
                    if (dealt == false) throw GameError("ERROR: Unknown command.");
                    cout << game.is_quarte() << endl;
                } else if (commands[i] == "quint?") {
                    if (dealt == false) throw GameError("ERROR: Unknown command.");
                    cout << game.is_quint() << endl;
                } else if (commands[i].find(':')) {
                    if (dealt == false) throw GameError("ERROR: Unknown command.");
                    istringstream hs(commands[i]);
                    string buff;
                    getline(hs, buff, ':');
                    if (buff == "highest_of_suit") {
                        getline(hs, buff);
                        if (buff == "spades") game.highest_of_suit('S');
                        else if (buff == "hearts") game.highest_of_suit('H');
                        else if (buff == "diamonds") game.highest_of_suit('D');
                        else if (buff == "clubs") game.highest_of_suit('C');
                        else throw GameError("ERROR: Unknown command.");
                    } else throw GameError("ERROR: Unknown command.");
                } else throw GameError("ERROR: Unknown command.");
            }
        } else if (commands[0] == "Santase") {
            Santase game;
            deck = game.get_deck();
            cout << deck << endl;
            for (size_t i = 1; i < commands.size(); i++) {
                if (common_commands<Santase>(commands[i], game, hand, dealt, deck)) {
                    //
                } else if (commands[i].find(':')) {
                    if (dealt == false) throw GameError("ERROR: Unknown command.");
                    istringstream hs(commands[i]);
                    string buff;
                    getline(hs, buff, ':');
                    if (buff == "twenty?") {
                        getline(hs, buff);
                        if (buff == "spades") cout << game.twenty('S') << endl;
                        else if (buff == "hearts") cout << game.twenty('H') << endl;
                        else if (buff == "diamonds") cout << game.twenty('D') << endl;
                        else if (buff == "clubs") cout << game.twenty('C') << endl;
                        else throw GameError("ERROR: Unknown command.");
                    } else if (buff == "fourty?") {
                        getline(hs, buff);
                        if (buff == "spades") cout << game.fourty('S') << endl;
                        else if (buff == "hearts") cout << game.fourty('H') << endl;
                        else if (buff == "diamonds") cout << game.fourty('D') << endl;
                        else if (buff == "clubs") cout << game.fourty('C') << endl;
                        else throw GameError("ERROR: Unknown command.");
                    } else throw GameError("ERROR: Unknown command.");
                } else throw GameError("ERROR: Unknown command.");
            }
        } else throw GameError("ERROR: Unknown command.");

    } catch(const GameError& err) {
        cerr << err.what() << endl;
    }

    return 0;
}
