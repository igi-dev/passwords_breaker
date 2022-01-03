#ifndef CONSUMER_H_
#define CONSUMER_H_

#include <pthread.h>
#include "StringConversion.h"
typedef struct Statistics
{
    int all, broken, left;
    float percentage_done;
} Statistics;

Statistics stats;

void *consume(void *arg);

void init_stats();

void recalculate_stats(int broken);

void print_stats(int sign);

#endif