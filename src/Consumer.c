
#include "Consumer.h"

void *consume(void *arg)
{
    int tid;
    threadData *data;
    data = (threadData *)arg;
    tid = data->threadID;
    pthread_mutex_t *broken_mutex = data->broken_table_mutex;
    pthread_mutex_t *found_mutex = data->found_cond_var_mutex;
    pthread_cond_t *found_cond_var = data->found_cond_var;
    int *n = data->n;
    bool *end_flag = data->end_flag;
    int iterations = 0;
    init_stats();
    int brkn = 0;

    signal(SIGHUP, &print_stats);

    for (int i = 0; i < PASSWORDS; ++i)
    {
        pthread_mutex_lock(found_mutex);
        while (*n == 0)
        {
            pthread_cond_wait(found_cond_var, found_mutex);
        }
        (*n)--;
        brkn++;
        recalculate_stats(brkn);
        pthread_mutex_unlock(found_mutex);
    }
    *end_flag = true;
    pthread_exit(NULL);
}

void init_stats()
{
    stats.all = PASSWORDS;
    stats.broken = 0;
    stats.left = PASSWORDS;
    stats.percentage_done = 0.0;
}

void recalculate_stats(int broken)
{
    stats.broken = broken;
    stats.left = PASSWORDS - broken;
    stats.percentage_done = ((float)broken / PASSWORDS) * 100;
}

void print_stats(int sign)
{
    printf("==================\n");
    printf("SUMMARY\n");
    printf("ALL PASSWORDS: %d\n", PASSWORDS);
    printf("ALREADY BROKEN: %d\n", stats.broken);
    printf("LEFT: %d\n", stats.left);
    printf("PERCENTAGE: %.3f\n", stats.percentage_done);
    printf("==================\n");
}