#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <Windows.h>
#include "player.h"
#include "game.h"
#include "stat_keeper.h"
#include "timingwheel.h"

static int player_id_generator = 0;

int total_number_of_players = 0;
int total_number_of_games = 0;

int total_table_players = 0;
int table_play = 0;

Player* player_generate(int* p, int* r, int* md, int* s, int* c) {
    int type = std::rand() % 100;
    if (type <= p[0]) {
        if (type <= r[0]) {
            return new RandomRedPlayer(++player_id_generator);
        } else if (type <= r[0] + r[1]) {
            return new RandomGreenPlayer(++player_id_generator);
        } else if (type <= r[0] + r[1] + r[2]) {
            return new RandomBluePlayer(++player_id_generator);
        } else {
            return new RandomBlackPlayer(++player_id_generator);
        }
    } else if (type <= p[0] + p[1]) {
        if (type <= md[0]) {
            return new MimicsRedDealer(++player_id_generator);
        } else if (type <= md[0] + md[1]) {
            return new MimicsGreenDealer(++player_id_generator);
        } else if (type <= md[0] + md[1] + md[2]) {
            return new MimicsBlueDealer(++player_id_generator);
        } else {
            return new MimicsBlackDealer(++player_id_generator);
        }
    } else if (type <= p[0] + p[1] + p[2]) {
        if (type <= s[0]) {
            return new SafeGreenPlayer(++player_id_generator);
        } else if (type <= s[0] + s[1]) {
            return new SafeGreenPlayer(++player_id_generator);
        } else if (type <= s[0] + s[1] + s[2]) {
            return new SafeBluePlayer(++player_id_generator);
        } else {
            return new SafeBlackPlayer(++player_id_generator);
        }
    } else {
        if (type <= c[0]) {
            return new MyRedPlayer(++player_id_generator);
        } else if (type <= c[0] + c[1]) {
            return new MyGreenPlayer(++player_id_generator);
        } else if (type <= c[0] + c[1] + c[2]) {
            return new MyBluePlayer(++player_id_generator);
        } else {
            return new MyBlackPlayer(++player_id_generator);
        }
    }
}

int tiktok;
int table_count;
int player_count_low, player_count_high;
int deck_count_low, deck_count_high;
int number_of_deals, salary, win_percentage;
int p[4];
int r[4], md[4], s[4], c[4];
float enter_percent;
int number_of_init_players;

void initialize(int argc, char** argv) {
    tiktok = std::atoi(argv[1]);
	//std::cout << "enter time";
	//std::cin >> tiktok;
    unsigned seed = unsigned ( std::time(0) );
    //std::cout << "Seed is " << seed << std::endl;
    std::srand ( seed );
    std::ifstream ifs("input.txt", std::ifstream::in);
    ifs >> table_count;
    ifs >> player_count_low >> player_count_high >> deck_count_low >> deck_count_high;
    int threshold1, threshold2, threshold3, threshold4;
    ifs >> threshold1 >> threshold2 >> threshold3 >> threshold4;

    ifs >> number_of_deals >> salary >> win_percentage;
    int miss;
    ifs >> miss >> miss;
    ifs >> number_of_init_players;
    ifs >> p[0] >> p[1] >> p[2] >> p[3];
    std::string misss;
    ifs >> misss >> r[0] >> r[1] >> r[2] >> r[3];
    ifs >> misss >> md[0] >> md[1] >> md[2] >> md[3];
    ifs >> misss >> s[0] >> s[1] >> s[2] >> s[3];
    ifs >> misss >> c[0] >> c[1] >> c[2] >> c[3];
    ifs >> enter_percent;
    ifs.close();
}

Game* game_ptr;

void print_status() {
    std::cout << "Duration of simulation: " << tiktok << std::endl;
    std::cout << "Total number of tables: " << table_count << std::endl;
    //todo the total money of the casino before and after the simulation
    //todo Dealer-wise performance in terms of win and loss percentage
    std::cout << "Total number of players: " << total_number_of_players << std::endl;
    double as = table_play?(total_table_players * 1.0 / table_play):0;
    std::cout << "Average number of players per table: " << as << std::endl;
    float rounds = 0;
    for (Player* player: game_ptr->total_players) {
        rounds += player->all_round();
    }
    std::cout << "Average playing rounds of each player: " << rounds * 1.0 / total_number_of_players << std::endl;
    float max_win_amount = 0, max_lose_amount = 0;
    for (Player* player: game_ptr->total_players) {
        if (player->win_amount > max_win_amount)
            max_win_amount = player->win_amount;
        if (player->loss_amount > max_lose_amount)
            max_lose_amount = player->loss_amount;
    }
    std::cout << "Maximum player win amount: " << max_win_amount << std::endl;
    std::cout << "Maximum player loss amount: " << max_lose_amount << std::endl;
    std::cout << "Total number of games played: " << total_number_of_games << std::endl;
    //todo Level-wise number of games
    //todo Number of times the refill cash event was generated
}

int main(int argc, char** argv) {
    initialize(argc, argv);
    //--------------
    int player_count = (std::rand() % (player_count_high - player_count_low + 1)) + player_count_low;
    int deck_count = (std::rand() % (deck_count_high - deck_count_low + 1)) + deck_count_low;

    game_ptr = new Game(table_count, player_count, deck_count, number_of_deals, win_percentage);
    for (int i = 0;i < number_of_init_players; ++i) {
        game_ptr->add_player(player_generate(p, r, md, s, c), 0);
    }
    total_number_of_players += number_of_init_players;

    TimingWheel wheel;
    wheel.game_ptr = game_ptr;
    for (auto it = game_ptr->tables.begin();it != game_ptr->tables.end(); ++it) {
        wheel.insert(1, &(*it));
    }

    for (int i = 1;i <= tiktok; ++i) {
        //simulate
        wheel.schedule();
        wheel.clear_curr_slot();
        for (auto it = game_ptr->tables.begin();it != game_ptr->tables.end(); ++it) {
            wheel.insert(1, &(*it));
        }
        wheel.current_slot = (wheel.current_slot + 1) % (max_delay + 1);
        Sleep(1);
        if (std::rand() % 100 < enter_percent * 100) {
            //add new player
            total_number_of_players += 1;
            game_ptr->add_player(player_generate(p, r, md, s, c), i);
        }
    }
    print_status();

    return 0;
}