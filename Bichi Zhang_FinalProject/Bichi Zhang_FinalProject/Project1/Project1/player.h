#ifndef POKER_PLAYER_H
#define POKER_PLAYER_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include "deck.h"

class Player {
public:
    Player(int id): player_id(id) {
        win = false;
        win_round = 0;
        lose_round = 0;
        cont_lose_round = 0;
        wait_begin_tik = -1;
        assign_amount(3000);
        loss_amount = 0;
        win_amount = 0;
    }

    int get_player_id() const { return player_id; }

    void add_card(Card c) {
        hands.push_back(c);
    }

    void clear_card() {
        hands.clear();
    }

    void add_amount(float a) {
        amount += a;
        win_amount += a;
    }

    void del_amount(float a) {
        amount -= a;
        lose_round += 1;
        cont_lose_round += 1;
        loss_amount += a;
    }

    bool is_bust() {
        int sum = get_hands_sum();
        return (sum > 21);
    }

    void assign_table(int tid) {
        table_number = tid;
    }

    void assign_amount(int a) {
        amount = a;
        init_amount = a;
    }

    float get_amount() const { return amount; }

    bool black_jack() {
        int sum = get_hands_sum();
        return hands.size() == 2 && sum == 21;
    }

    int get_hands_sum() const {
        int sum = 0;
        for (Card hand: hands) {
            if (hand.value >= 10) {
                sum += 10;
            } else if (hand.value == 1&&sum<11) {
                sum += 11;
            } else {
                sum += hand.value;
            }
        }
        return sum;
    }

    void show_hands() {
        for (Card hand: hands) {
            std::cout << hand.to_string() << ",";
        }
    }

    bool is_win() const { return win; }

    void set_win(bool w) {
        win = w;
        win_round += 1;
        cont_lose_round = 0;
    }

    int get_bet() { return bet_amount; }

    virtual bool should_leave() = 0;

    virtual void bet() = 0;
    virtual bool play() = 0;

    void reset() {
        table_number = 0;
        win_round = lose_round = 0;
    }

    void set_wait_begin_tik(int tik) {
        wait_begin_tik = tik;
    }

    int get_wait_begin_tik() const { return wait_begin_tik; }

    int all_round() const { return win_round + lose_round; }

    virtual void report_done() = 0;

    int loss_amount;
    int win_amount;

protected:
    int player_id;
    int table_number;
    int wait_begin_tik;
    float amount;
    float init_amount;
    int bet_amount;
    int cont_lose_round;
    bool win;
    std::vector<Card> hands;
    int win_round;
    int lose_round;
};

class RandomPlayer: public Player {
public:
    RandomPlayer(int id): Player(id) {
    }

    bool play() {
        //Uses his/her hunch to decide on a hit or stay
        //random
        return rand() % 2 == 1;
    }
    void bet() {}
    bool should_leave() {return false;}
    void report_done() {
        std::cout << player_id << ", " << "RandomPlayer ";
        if (win) {
            std::cout << "won " << win_amount;
        } else {
            std::cout << "lost " << loss_amount;
        }
        std::cout << " on " << table_number << std::endl;
    }
};

class SafePlayer: public Player {
public:
    SafePlayer(int id): Player(id) {
    }

    bool play() {
        //refuses to hit any hand that might bust
        int sum = get_hands_sum();
        if (21 - sum <= 11) {
            return false;
        }
        return true;
    }
    void bet() {}
    bool should_leave() {return false;}
    void report_done() {
        std::cout << player_id << ", " << "SafePlayer ";
        if (win) {
            std::cout << "won " << win_amount;
        } else {
            std::cout << "lost " << loss_amount;
        }
        std::cout << " on " << table_number << std::endl;
    }
};

class MimicsDealer: public Player {
public:
    MimicsDealer(int id): Player(id) {
    }

    bool play() {
        //Hits all hands 16 or less and stays on hands that are 17 or more
        int sum = get_hands_sum();
        if (sum <= 16) {
            return true;
        }
        return false;
    }
    void bet() {}
    bool should_leave() {return false;}
    void report_done() {
        std::cout << player_id << ", " << "MimicsDealer ";
        if (win) {
            std::cout << "won " << win_amount;
        } else {
            std::cout << "lost " << loss_amount;
        }
        std::cout << " on " << table_number << std::endl;
    }
};

class MyPlayer: public Player {
public:
    MyPlayer(int id): Player(id) {
    }

    bool play() {
        int sum = get_hands_sum();
        if (sum >= 18) {
            return false;
        }
        return true;
    }
    void bet() {}
    bool should_leave() {return false;}
    void report_done() {
        std::cout << player_id << ", " << "MyPlayer ";
        if (win) {
            std::cout << "won " << win_amount;
        } else {
            std::cout << "lost " << loss_amount;
        }
        std::cout << " on " << table_number << std::endl;
    }
};

class RandomRedPlayer: public RandomPlayer {
public:
    RandomRedPlayer(int id): RandomPlayer(id) {

    }

    void bet() {
        bet_amount = (rand() % 9 + 1) * 5;
    }
    bool should_leave() {
        return (lose_round + win_round) * 0.6 < lose_round && (lose_round+win_round)>1;
    }
    void report_done() {
        std::cout << player_id << ", " << "RandomRedPlayer ";
        if (win) {
            std::cout << "won " << win_amount;
        } else {
            std::cout << "lost " << loss_amount;
        }
        std::cout << " on " << table_number << std::endl;
    }
};

class RandomGreenPlayer: public RandomPlayer {
public:
    RandomGreenPlayer(int id): RandomPlayer(id) {

    }

    void bet() {
        bet_amount = (rand() % 10) * 5 + 50;
    }
    bool should_leave() {
        return init_amount * 0.1 >= amount;
    }
    void report_done() {
        std::cout << player_id << ", " << "RandomGreenPlayer ";
        if (win) {
            std::cout << "won " << win_amount;
        } else {
            std::cout << "lost " << loss_amount;
        }
        std::cout << " on " << table_number << std::endl;
    }
};

class RandomBluePlayer: public RandomPlayer {
public:
    RandomBluePlayer(int id): RandomPlayer(id) {

    }

    void bet() {
        bet_amount = (rand() % 40) * 10 + 100;
    }
    bool should_leave() {
        return cont_lose_round  == 3;
    }
    void report_done() {
        std::cout << player_id << ", " << "RandomBluePlayer ";
        if (win) {
            std::cout << "won " << win_amount;
        } else {
            std::cout << "lost " << loss_amount;
        }
        std::cout << " on " << table_number << std::endl;
    }
};

class RandomBlackPlayer: public RandomPlayer {
public:
    RandomBlackPlayer(int id): RandomPlayer(id) {

    }

    void bet() {
        bet_amount = (rand() % 6) * 100 + 500;
    }
    bool should_leave() {
        return (lose_round + win_round) == 10;
    }
    void report_done() {
        std::cout << player_id << ", " << "RandomBlackPlayer ";
        if (win) {
            std::cout << "won " << win_amount;
        } else {
            std::cout << "lost " << loss_amount;
        }
        std::cout << " on " << table_number << std::endl;
    }
};

class SafeRedPlayer: public SafePlayer {
public:
    SafeRedPlayer(int id): SafePlayer(id) {

    }

    void bet() {
        bet_amount = (rand() % 9 + 1) * 5;
    }
    bool should_leave() {
        return (lose_round + win_round) * 0.6 < lose_round && (lose_round + win_round)>1;
    }
    void report_done() {
        std::cout << player_id << ", " << "SafeRedPlayer ";
        if (win) {
            std::cout << "won " << win_amount;
        } else {
            std::cout << "lost " << loss_amount;
        }
        std::cout << " on " << table_number << std::endl;
    }
};

class SafeGreenPlayer: public SafePlayer {
public:
    SafeGreenPlayer(int id): SafePlayer(id) {

    }

    void bet() {
        bet_amount = (rand() % 10) * 5 + 50;
    }
    bool should_leave() {
        return init_amount * 0.1 >= amount;
    }
    void report_done() {
        std::cout << player_id << ", " << "SafeGreenPlayer ";
        if (win) {
            std::cout << "won " << win_amount;
        } else {
            std::cout << "lost " << loss_amount;
        }
        std::cout << " on " << table_number << std::endl;
    }
};

class SafeBluePlayer: public SafePlayer {
public:
    SafeBluePlayer(int id): SafePlayer(id) {

    }

    void bet() {
        bet_amount = (rand() % 40) * 10 + 100;
    }
    bool should_leave() {
        return cont_lose_round  == 3;
    }
    void report_done() {
        std::cout << player_id << ", " << "SafeBluePlayer ";
        if (win) {
            std::cout << "won " << win_amount;
        } else {
            std::cout << "lost " << loss_amount;
        }
        std::cout << " on " << table_number << std::endl;
    }
};

class SafeBlackPlayer: public SafePlayer {
public:
    SafeBlackPlayer(int id): SafePlayer(id) {

    }

    void bet() {
        bet_amount = (rand() % 6) * 100 + 500;
    }
    bool should_leave() {
        return (lose_round + win_round) == 10;
    }
    void report_done() {
        std::cout << player_id << ", " << "SafeBlackPlayer ";
        if (win) {
            std::cout << "won " << win_amount;
        } else {
            std::cout << "lost " << loss_amount;
        }
        std::cout << " on " << table_number << std::endl;
    }
};

class MimicsRedDealer: public MimicsDealer {
public:
    MimicsRedDealer(int id): MimicsDealer(id) {

    }

    void bet() {
        bet_amount = (rand() % 9 + 1) * 5;
    }
    bool should_leave() {
        return (lose_round + win_round) * 0.6 < lose_round && (lose_round + win_round)>1;
    }
    void report_done() {
        std::cout << player_id << ", " << "MimicsRedDealer ";
        if (win) {
            std::cout << "won " << win_amount;
        } else {
            std::cout << "lost " << loss_amount;
        }
        std::cout << " on " << table_number << std::endl;
    }
};

class MimicsGreenDealer: public MimicsDealer {
public:
    MimicsGreenDealer(int id): MimicsDealer(id) {

    }

    void bet() {
        bet_amount = (rand() % 10) * 5 + 50;
    }
    bool should_leave() {
        return init_amount * 0.1 >= amount;
    }
    void report_done() {
        std::cout << player_id << ", " << "MimicsGreenDealer ";
        if (win) {
            std::cout << "won " << win_amount;
        } else {
            std::cout << "lost " << loss_amount;
        }
        std::cout << " on " << table_number << std::endl;
    }
};

class MimicsBlueDealer: public MimicsDealer {
public:
    MimicsBlueDealer(int id): MimicsDealer(id) {

    }

    void bet() {
        bet_amount = (rand() % 40) * 10 + 100;
    }
    bool should_leave() {
        return cont_lose_round  == 3;
    }
    void report_done() {
        std::cout << player_id << ", " << "MimicsBlueDealer ";
        if (win) {
            std::cout << "won " << win_amount;
        } else {
            std::cout << "lost " << loss_amount;
        }
        std::cout << " on " << table_number << std::endl;
    }
};

class MimicsBlackDealer: public MimicsDealer {
public:
    MimicsBlackDealer(int id): MimicsDealer(id) {

    }

    void bet() {
        bet_amount = (rand() % 6) * 100 + 500;
    }
    bool should_leave() {
        return (lose_round + win_round) == 10;
    }
    void report_done() {
        std::cout << player_id << ", " << "MimicsBlackDealer ";
        if (win) {
            std::cout << "won " << win_amount;
        } else {
            std::cout << "lost " << loss_amount;
        }
        std::cout << " on " << table_number << std::endl;
    }
};

class MyRedPlayer: public MyPlayer {
public:
    MyRedPlayer(int id): MyPlayer(id) {

    }

    void bet() {
        bet_amount = (rand() % 9 + 1) * 5;
    }
    bool should_leave() {
        return (lose_round + win_round) * 0.6 < lose_round && (lose_round + win_round)>1;
    }
    void report_done() {
        std::cout << player_id << ", " << "MyRedPlayer ";
        if (win) {
            std::cout << "won " << win_amount;
        } else {
            std::cout << "lost " << loss_amount;
        }
        std::cout << " on " << table_number << std::endl;
    }
};

class MyGreenPlayer: public MyPlayer {
public:
    MyGreenPlayer(int id): MyPlayer(id) {

    }

    void bet() {
        bet_amount = (rand() % 10) * 5 + 50;
    }
    bool should_leave() {
        return init_amount * 0.1 >= amount;
    }
    void report_done() {
        std::cout << player_id << ", " << "MyGreenPlayer ";
        if (win) {
            std::cout << "won " << win_amount;
        } else {
            std::cout << "lost " << loss_amount;
        }
        std::cout << " on " << table_number << std::endl;
    }
};

class MyBluePlayer: public MyPlayer {
public:
    MyBluePlayer(int id): MyPlayer(id) {

    }

    void bet() {
        bet_amount = (rand() % 40) * 10 + 100;
    }
    bool should_leave() {
        return cont_lose_round  == 3;
    }
    void report_done() {
        std::cout << player_id << ", " << "MyBluePlayer ";
        if (win) {
            std::cout << "won " << win_amount;
        } else {
            std::cout << "lost " << loss_amount;
        }
        std::cout << " on " << table_number << std::endl;
    }
};

class MyBlackPlayer: public MyPlayer {
public:
    MyBlackPlayer(int id): MyPlayer(id) {

    }

    void bet() {
        bet_amount = (rand() % 6) * 100 + 500;
    }
    bool should_leave() {
        return (lose_round + win_round) == 10;
    }
    void report_done() {
        std::cout << player_id << ", " << "MyBlackPlayer ";
        if (win) {
            std::cout << "won " << win_amount;
        } else {
            std::cout << "lost " << loss_amount;
        }
        std::cout << " on " << table_number << std::endl;
    }
};

#endif //POKER_PLAYER_H
