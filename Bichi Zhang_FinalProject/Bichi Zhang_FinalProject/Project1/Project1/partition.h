#ifndef __PARTITION_H__
#define __PARTITION_H__

#include "table.h"

class Partition {
    BlackjackTable* gtp;
    Partition *nextp;
public:
    Partition(BlackjackTable* g, Partition *next): gtp(g), nextp(next) {}
    BlackjackTable* get_gtp() const { return gtp; }
    Partition * get_next() const { return nextp; }
};

#endif