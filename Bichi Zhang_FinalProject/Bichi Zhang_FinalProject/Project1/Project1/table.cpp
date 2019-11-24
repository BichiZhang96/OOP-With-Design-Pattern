#include "table.h"
#include "stat_keeper.h"

BlackjackTable::BlackjackTable(int id, int deck_count, int cap):
        table_number(id),
        dealer(-1, 0),
        deck(deck_count),
        player_count(0),
        capacity(cap)
{
}

void BlackjackTable::add_player(Player* player) {
    player_count += 1;
    players.push_back(player);
    player->assign_table(table_number);
}

void BlackjackTable::bet() {
    dealer.clear_card();
    for (Player* player: players) {
        player->clear_card();
        player->bet();
        std::cout << "player " << player->get_player_id() << " bet " << player->get_bet() << std::endl;
    }
}

void BlackjackTable::dealing() {
    for (int i = 0;i < 2; ++i) {
        for (Player* player: players) {
            player->add_card(deck.hit_card());
        }
    }
    dealer.add_card(deck.hit_card());
}

void BlackjackTable::playing() {
    total_table_players += players.size();
    table_play += 1;
    dealer.add_card(deck.hit_card());
    bool win = false;
    for (Player* player: players) {
        if (player->black_jack()) {
            player->set_win(true);
            if (dealer.get_hands_sum() != 21) {
                player->add_amount(player->get_bet() * 1.5);
            }
            win = true;
        }
    }
    if (win) {
        dealer.lose_count += 1;
        return ;
    }
    bool cont = false;
    while (!cont) {
        cont = false;
        for (Player* player: players) {
			for (int i = 0; i < 5; i++)
			{
				if (!player->is_bust() && player->play()) {
					player->add_card(deck.hit_card());
					cont = true;
				}
			}
        }
		for (int i = 0; i < 5; i++)
		{
			if (!dealer.is_stay()) {
				cont = true;
				dealer.add_card(deck.hit_card());
			}
		}
        if (dealer.is_bust()) {
           dealer.lose_count += 1;
           for (Player* player: players) {
                player->set_win(true);
                player->add_amount(player->get_bet());
            }
            return ;
        }
    }
    bool dealer_lose = true;
    for (Player* player: players) {
        if (!player->is_bust() &&
            player->get_hands_sum() > dealer.get_hands_sum()) {
            player->set_win(true);
            player->add_amount(player->get_bet());
        } 
		else if(!player->is_bust() &&
			player->get_hands_sum() < dealer.get_hands_sum()) {
			player->del_amount(player->get_bet());
			dealer_lose = false;
		}
		else if (player->is_bust())
		{
			player->del_amount(player->get_bet());
		}
		else {
            dealer_lose = false;
        }
    }
    if (dealer_lose) {
        dealer.lose_count += 1;
    } else {
        dealer.win_count += 1;
    }
}

void BlackjackTable::result() {
    std::cout << "Dealer: ";
    dealer.show_hands();
    std::cout << " sum: " << dealer.get_hands_sum() << std::endl;
    dealer.clear_card();
    for (Player* player: players) {
        std::cout << "Player " << player->get_player_id() << ": ";
        player->show_hands();
        std::cout << " ";
        std::cout << "sum: " << player->get_hands_sum() << " ";
        std::cout << "bet amount: " << player->get_bet() << std::endl;
    }
    for (Player* player: players) {
        std::cout << "Player " << player->get_player_id() << " ";
        if (player->is_win()) {
            std::cout << "wins, ";
        } else {
            std::cout << "loses, ";
        }
        std::cout << "balance: " << player->get_amount() << std::endl;
        player->clear_card();
    }
}

std::vector<Player*> BlackjackTable::clear_player() {
    std::vector<Player*> leave;
    std::vector<Player*> stay;
    for (Player* player: players) {
        if (player->should_leave()) {
            leave.push_back(player);
        } else {
            stay.push_back(player);
        }
    }
    players.clear();
    for (Player* player: stay) {
        players.push_back(player);
    }
    player_count = players.size();
    return leave;
}
