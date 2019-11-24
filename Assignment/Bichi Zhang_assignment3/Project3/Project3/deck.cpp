#include "deck.h"
#include <random>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <time.h>

using namespace std;

ostream& operator<<(ostream& out, const Card& rhs) {
    out << rhs.color << "-" << rhs.value;
    return out;
}

void Deck::reset() {
    string colors[4] = {"Club", "Diamond", "Heart", "Spade"};
    string values[13] = {"Ace", "King", "Queen", "Jack", "10", "9", "8", "7", "6", "5", "4", "3", "2"};
    for (int i = 0;i < 4; ++i) {
        for (int j = 0;j < 13; ++j) {
            Card card(colors[i], values[j]);
            cards.push_back(card);
        }
    }
	//for (list<Card>::iterator it = cards.begin(); it != cards.end(); ++it) {
		//vect.push_back(*it);
		//cout << *it;
	//}

}

Deck::Deck() {
    reset();
}

void Deck::simulate_shuffling() {
    vector<Card> vect;
    for (list<Card>::iterator it = cards.begin();it != cards.end(); ++it) {
        vect.push_back(*it);
    }
    random_shuffle(vect.begin(), vect.end());
    list<Card> new_cards;
    for (vector<Card>::iterator it = vect.begin();it != vect.end(); ++it) {
        new_cards.push_back(*it);
    }
    cards = new_cards;
}

Card Deck::hand_one() {
    Card card = cards.front();
    cards.pop_front();
    return card;
}

void Deck::restore(Card& card) {
    cards.push_back(card);
}