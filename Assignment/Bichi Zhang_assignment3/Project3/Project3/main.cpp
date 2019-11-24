#include "deck.h"
#include <iomanip>
#include <vector>
#include <time.h>

using namespace std;

void one_player_hand(string name, Deck& deck) {
    Card cards[4];
    cout << setw (5) <<name << ": ";
    for (int i = 0;i < 4; ++i) {
        cards[i] = deck.hand_one();
        cout << cards[i] << " ";
    }
    cout << endl;
}

void domain() {
    Deck deck;
    deck.simulate_shuffling();
	vector <string> players;
	players = {"North", "East", "South", "West"};
    cout << "round 1:" << endl;
    for (int i = 0;i < 4; ++i) {
        cout << setw(5) <<players[i] << ": ";
        for (int j = 0;j < 5; ++j) {
            cout << deck.hand_one() << " ";
        }
        cout << endl;
    }
    int round = 2;
    while (!deck.is_empty()) {
        cout << "round " << round++ << ":" << endl;
        for (int i = 0;i < 4; ++i) {
            one_player_hand(players[i], deck);
        }
    }
}

int main() {
    string input;
    while (true) {
        domain();
        cout << "repeat? (y/n) ";
        cin >> input;
        if (input != "y") {
            break;
        }
    }
    return 0;
}