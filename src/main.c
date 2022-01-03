#include "StringConversion.h"
#include "Producer.h"
#include "Consumer.h"
#include <string.h>
#include <signal.h>
#define DEFAULT_DICTIONARY "../dictionaries/cracklib-small"
#define DEFAULT_PASSWORDS "../passwords/my_passwords.txt"

int main(int argc, char **argv)
{
    int n = 0;
    bool end_flag = false;
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    pthread_mutex_t broken_table_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t found_cond_var_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t found_cond_var = PTHREAD_COND_INITIALIZER;
    void *status;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    int lines_count = countlines("../dictionaries/cracklib-small");
    char *dictionary[lines_count];
    init_dictionary(dictionary, lines_count, DEFAULT_DICTIONARY);
    init_passwords_table(DEFAULT_PASSWORDS, PASSWORDS);
    for (int t = 0; t < NUM_THREADS; t++)
    {
        threadDataArray[t].threadID = t;
        threadDataArray[t].dictionary = dictionary;
        threadDataArray[t].dictionary_entries = lines_count;
        threadDataArray[t].broken_table_mutex = &broken_table_mutex;
        threadDataArray[t].found_cond_var = &found_cond_var;
        threadDataArray[t].found_cond_var_mutex = &found_cond_var_mutex;
        threadDataArray[t].n = &n;
        threadDataArray[t].end_flag = &end_flag;
        if (t == 0)
            pthread_create(&threads[t], &attr, produce1, (void *)&threadDataArray[t]);
        else if (t == 1)
            pthread_create(&threads[t], &attr, produce2, (void *)&threadDataArray[t]);
        else if (t == 2)
            pthread_create(&threads[t], &attr, produce3, (void *)&threadDataArray[t]);
        else if (t == 3)
            pthread_create(&threads[t], &attr, consume, (void *)&threadDataArray[t]);
        else if (t == 4)
            pthread_create(&threads[t], &attr, produce_double1, (void *)&threadDataArray[t]);
        else if (t == 5)
            pthread_create(&threads[t], &attr, produce_double2, (void *)&threadDataArray[t]);
    }
    pthread_attr_destroy(&attr);
    for (int i = 0; i < NUM_THREADS; ++i)
        pthread_join(threads[i], &status);
    printf("\nALL PASSWORDS HAVE BEEN BROKEN\n\nGOODBYE :)\n\n");
    free_dictionary(dictionary, lines_count);
    pthread_exit(NULL);
    return EXIT_SUCCESS;
}