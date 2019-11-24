#ifndef __TIMINGWHEEL_H__
#define __TIMINGWHEEL_H__
#define max_delay 100


#include "partition.h"
#include "game.h"


class TimingWheel
{
    Partition * slot[max_delay + 1];
    //max_delay (max play time possible for one round of play)
public:
    int current_slot;
    Game* game_ptr;
public:
    TimingWheel();
    void insert(int play_time, BlackjackTable* p1);
    void schedule();
    void clear_curr_slot();
};

#endif