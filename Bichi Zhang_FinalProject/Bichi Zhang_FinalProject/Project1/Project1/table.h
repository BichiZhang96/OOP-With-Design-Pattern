#ifndef POKER_TABLE_H
#define POKER_TABLE_H

#include "dealer.h"
#include "player.h"
#include <vector>

class BlackjackTable {
public:
    BlackjackTable(int id, int deck_count, int cap);

    void assign_dealer(Dealer d) {
        dealer = d;
    }

    bool can_play() {
        return players.size() != 0;
    }

    Dealer& get_dealer() { return dealer; }

    bool has_position() {
        return player_count < capacity;
    }

    void add_player(Player* player);

    void bet();

    void dealing();

    void playing();

    void result();

    std::vector<Player*> clear_player();
public:
    int table_number;
private:
    Deck deck;
    Dealer dealer;
    std::vector<Player*> players;
    int player_count;
    int capacity;
};

#endif //POKER_TABLE_H
