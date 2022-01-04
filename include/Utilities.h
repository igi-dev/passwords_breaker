#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <signal.h>

#define PASSWORDS 4
#define NUM_THREADS 6


typedef struct threadData
{
    int threadID;
    int dictionary_entries;
    char **dictionary;
    pthread_mutex_t *broken_table_mutex;
    pthread_cond_t *found_cond_var;
    pthread_mutex_t *found_cond_var_mutex;
    int *n;
    bool *end_flag;
} threadData;

threadData threadDataArray[NUM_THREADS];

char passwords[PASSWORDS][33];
bool broken[PASSWORDS];

int countlines(char *filename);

void read_passwords(char *name, int size, char output_array[][33]);

void init_passwords_table(char *filename, int size);

void init_dictionary(char **dict, int lines_count, char *filename);

void free_dictionary(char **dict, int lines_count);

int check_password_match(char passwords_table[][33], char *md5_str);

#endif