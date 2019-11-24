#ifndef POKER_DEALER_H
#define POKER_DEALER_H

#include <vector>
#include <iostream>
#include "deck.h"

class Dealer {
public:
    Dealer(int id, int wp);

    void add_card(Card c) {
        hands.push_back(c);
    }

    void clear_card() {
        hands.clear();
    }

    bool is_bust() {
        int sum = get_hands_sum();
        return (sum > 21);
    }

    bool is_stay() {
        int sum = get_hands_sum();
        return (sum >= 17);
    }

    void show_hands();

    int get_hands_sum();

    bool should_leave() {
        return (win_count + lose_count) * 0.01 * win_percent > win_count;
    }

    void reset() {
        win_count = lose_count = round_count = 0;
        amount = 10000;
    }

private:
    int employee_id;
    int round_count;
    float amount;
    int win_percent;
    std::vector<Card> hands;

public:
    int win_count;
    int lose_count;
};

#endif //POKER_DEALER_H
