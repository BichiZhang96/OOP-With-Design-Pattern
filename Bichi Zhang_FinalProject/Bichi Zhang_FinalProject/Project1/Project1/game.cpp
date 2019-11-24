#include "game.h"
#include "stat_keeper.h"

Game::Game(int table_count, int player_count, int deck_count, int number_of_deals,
     int win_percentage) {
    for (int i = 0;i < table_count; ++i) {
        BlackjackTable table(i, deck_count, player_count);
        tables.push_back(table);
    }
    for (int i = 0;i < number_of_deals; ++i) {
        Dealer dealer(i, win_percentage);
        dealer_queue.push_back(dealer);
    }

    for (std::vector<BlackjackTable>::iterator it = tables.begin();it != tables.end(); ++it) {
        Dealer dealer = dealer_queue.front();
        dealer_queue.pop_front();
        it->assign_dealer(dealer);
    }
}

void Game::add_player(Player* player, int tiktok) {
    total_players.push_back(player);
    for (std::vector<BlackjackTable>::iterator it = tables.begin();it != tables.end(); ++it) {
        if (it->has_position()) {
            it->add_player(player);
            std::cout << "player " << player->get_player_id() << " enter table " << it->table_number << std::endl;
            return ;
        }
    }
    std::cout << "player " << player->get_player_id() << " wait in the queue" << std::endl;
    player->set_wait_begin_tik(tiktok);
    player_queue.push_back(player);
}