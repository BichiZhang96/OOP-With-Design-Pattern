#include "deck.h"
#include <algorithm>

std::string Card::to_string() {
    std::string str = "";
    if (color == 1) str = "Heart";
    else if (color == 2) str = "Spade";
    else if (color == 3) str = "Diamond";
    else str = "Club";
    std::string tp[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    str += tp[value - 1];
    return str;
}

Deck::Deck(int decks) {
    for (int i = 0;i < decks; ++i) {
        for (int color = 1;color <= 4; ++color) {
            for (int value = 1;value <= 13; ++value) {
                Card card;
                card.color = color;
                card.value = value;
                cards.push_back(card);
            }
        }
    }
    std::random_shuffle(cards.begin(), cards.end());
}

Card Deck::hit_card()
{
    Card card = cards.back();
    cards.pop_back();
    return card;
}