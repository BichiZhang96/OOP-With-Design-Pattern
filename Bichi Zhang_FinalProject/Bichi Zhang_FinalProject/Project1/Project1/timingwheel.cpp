#include "timingwheel.h"
#include "stat_keeper.h"

TimingWheel::TimingWheel(): current_slot(0)
{
    for (int i = 0;i < max_delay + 1; ++i)
    {
        slot[i] = NULL;
    }
}

void TimingWheel::insert(int play_time, BlackjackTable* p1)
{
    int position = play_time + current_slot;
    position %= (max_delay + 1);
    Partition* partition = new Partition(p1, slot[position]);
    slot[position] = partition;
}

void TimingWheel::schedule()
{
    Partition* curr = slot[current_slot];

    bool has_empty = true;
    while (!game_ptr->player_queue.empty() && has_empty) {
        has_empty = false;
        while (curr)
        {
            if (curr->get_gtp()->has_position()) {
                has_empty = true;
                if (game_ptr->player_queue.empty()) {
                    break;
                }
                Player* player = game_ptr->player_queue.front();
                game_ptr->player_queue.pop_front();
                curr->get_gtp()->add_player(player);
                std::cout << "player " << player->get_player_id() << " enter table " << curr->get_gtp()->table_number << std::endl;
            }
            curr = curr->get_next();
        }
    }
    curr = slot[current_slot];
    while (curr)
    {
        std::cout << "[table-" << curr->get_gtp()->table_number << "]" << std::endl;
        if (!curr->get_gtp()->can_play()) {
            std::cout << "no player on this table" << std::endl;
        } else {
            total_number_of_games += 1;
            curr->get_gtp()->bet();
            curr->get_gtp()->dealing();
            curr->get_gtp()->playing();
            curr->get_gtp()->result();

            Dealer dealer = curr->get_gtp()->get_dealer();
            if (dealer.should_leave() && !game_ptr->dealer_queue.empty()) {
                dealer.reset();
                game_ptr->dealer_queue.push_back(dealer);

                dealer = game_ptr->dealer_queue.front();
                game_ptr->dealer_queue.pop_front();
                curr->get_gtp()->assign_dealer(dealer);
            }

            std::vector<Player*> leave_players = curr->get_gtp()->clear_player();
            for (Player* player: leave_players) {
                std::cout << "player " << player->get_player_id() << " leave table " << curr->get_gtp()->table_number << std::endl;
                player->report_done();
                player->reset();
                //player_queue.push_back(player);
            }
        }
        curr = curr->get_next();
    }
}

void TimingWheel::clear_curr_slot()
{
    Partition* curr = slot[current_slot];
    Partition* target;
    while (curr)
    {
        target = curr;
        curr = curr->get_next();
        delete target;
    }
}