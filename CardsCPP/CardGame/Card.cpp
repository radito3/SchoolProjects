#include "Card.hh"

std::ostream &operator<<(std::ostream &out, const Card &card) {
    out << card.suit << card.rank;
    return out;
}

std::ostream &operator<<(std::ostream &out, const Card::Suit &suit) {
    switch (suit) {
        case Card::Suit::CLUBS:
            out << 'C';
            break;
        case Card::Suit::DIAMONDS:
            out << 'D';
            break;
        case Card::Suit::HEARTS:
            out << 'H';
            break;
        case Card::Suit::SPADES:
            out << 'S';
            break;
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, const Card::Rank &rank) {
    switch (rank) {
        case Card::Rank::TWO:
            out << '2';
            break;
        case Card::Rank::THREE:
            out << '3';
            break;
        case Card::Rank::FOUR:
            out << '4';
            break;
        case Card::Rank::FIVE:
            out << '5';
            break;
        case Card::Rank::SIX:
            out << '6';
            break;
        case Card::Rank::SEVEN:
            out << '7';
            break;
        case Card::Rank::EIGHT:
            out << '8';
            break;
        case Card::Rank::NINE:
            out << '9';
            break;
        case Card::Rank::TEN:
            out << "10";
            break;
        case Card::Rank::JACK:
            out << 'J';
            break;
        case Card::Rank::QUEEN:
            out << 'Q';
            break;
        case Card::Rank::KING:
            out << "K";
            break;
        case Card::Rank::ACE:
            out << 'A';
            break;
    }
    return out;
}
