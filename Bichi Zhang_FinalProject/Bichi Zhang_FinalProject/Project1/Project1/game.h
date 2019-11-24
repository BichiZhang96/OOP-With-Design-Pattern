#ifndef POKER_GAME_H
#define POKER_GAME_H

#include <vector>
#include <list>
#include "deck.h"
#include "dealer.h"
#include "table.h"

class Game {
public:
    Game(int table_count, int player_count, int deck_count, int number_of_deals,
            int win_percentage);
    void add_player(Player* player, int tiktok);
    std::list<Player*> total_players;
    std::vector<BlackjackTable> tables;
    std::list<Dealer> dealer_queue;
    std::list<Player*> player_queue;
};

#endif //POKER_GAME_H
