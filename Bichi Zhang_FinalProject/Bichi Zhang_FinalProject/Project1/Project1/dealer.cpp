#include "dealer.h"

Dealer::Dealer(int id, int wp): employee_id(id),
                        win_count(0),
                        lose_count(0),
                        round_count(0),
                        amount(1000),
                        win_percent(wp) {

}

void Dealer::show_hands() {
    for (Card hand: hands) {
        std::cout << hand.to_string() << ",";
    }
}

int Dealer::get_hands_sum() {
    int sum = 0;
    for (Card hand: hands) {
        if (hand.value >= 10) {
            sum += 10;
        } else if (hand.value == 1 && sum<11) {
            sum += 11;
        } else {
            sum += hand.value;
        }
    }
    return sum;
}


