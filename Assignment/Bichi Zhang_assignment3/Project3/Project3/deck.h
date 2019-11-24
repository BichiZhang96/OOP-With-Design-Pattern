#include <string>
#include <iostream>
#include <list>

using namespace std;

class Card {
public:
    Card() {}
    Card(string c, string v):
            color(c), value(v) {
    }
    friend ostream& operator<<(ostream& out, const Card& rhs);
private:
    string color;
    string value;
};
//In each suit, the cards are labeled Ace, King, Queen, Jack, 10, 9, …, 2
class Deck {
public:
    Deck();
    void reset();
    void simulate_shuffling();
    Card hand_one();
    void restore(Card& card);
    bool is_empty() { return cards.empty(); }
private:
    list<Card> cards;
};
