#ifndef POKER_DECK_H
#define POKER_DECK_H

#include <string>
#include <vector>

struct Card {
    int color;
    int value;

    std::string to_string();
};

class Deck {
public:
    Deck(int decks);

    bool no_card_left() { return cards.size() == 0; }

    Card hit_card();

private:
    std::vector<Card> cards;
};

#endif //POKER_DECK_H
