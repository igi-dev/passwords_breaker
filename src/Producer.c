#include "Producer.h"

void *produce1(void *arg)
{
    int tid, dict_entries;
    threadData *data;
    data = (threadData *)arg;
    tid = data->threadID;
    char **dict = data->dictionary;
    dict_entries = data->dictionary_entries;
    pthread_mutex_t *broken_mutex = data->broken_table_mutex;
    pthread_mutex_t *found_mutex = data->found_cond_var_mutex;
    pthread_cond_t *found_cond_var = data->found_cond_var;
    int *n = data->n;
    bool *end_flag = data->end_flag;

    sigset_t set;
    sigaddset(&set, SIGHUP);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    if (tid == 0) //all lowercase
    {
        int iterations = 0;
        int found = -1;
        int h = 0;
        while ((*end_flag) == false)
        {
            for (int i = 0; i < dict_entries; ++i)
            {
                if (iterations == 0)
                {
                    int length = strlen(dict[i]);
                    char *to_check = (char *)malloc((length + 1) * sizeof(char));
                    strcpy(to_check, dict[i]);
                    char *md5 = (char *)malloc(33 * sizeof(char));
                    str2md5(to_check, strlen(to_check), md5);
                    found = check_password_match(passwords, md5);
                    if (found >= 0)
                    {
                        pthread_mutex_lock(broken_mutex);
                        broken[found] = true;
                        pthread_mutex_unlock(broken_mutex);
                        pthread_mutex_lock(found_mutex);
                        (*n)++;
                        pthread_cond_signal(found_cond_var);
                        pthread_mutex_unlock(found_mutex);
                    }
                    free(md5);
                    free(to_check);
                }
                else if (h == 0)
                {
                    int length = snprintf(NULL, 0, "%s%d", dict[i], iterations);
                    char *to_check = (char *)malloc((length + 1) * sizeof(char));
                    snprintf(to_check, length + 1, "%s%d", dict[i], iterations);
                    char *md5 = (char *)malloc(33 * sizeof(char));
                    str2md5(to_check, strlen(to_check), md5);
                    found = check_password_match(passwords, md5);
                    if (found >= 0)
                    {
                        pthread_mutex_lock(broken_mutex);
                        broken[found] = true;
                        pthread_mutex_unlock(broken_mutex);
                        pthread_mutex_lock(found_mutex);
                        (*n)++;
                        pthread_cond_signal(found_cond_var);
                        pthread_mutex_unlock(found_mutex);
                    }
                    free(md5);
                    free(to_check);
                }
                else if (h == 1)
                {
                    int length = snprintf(NULL, 0, "%d%s", iterations, dict[i]);
                    char *to_check = (char *)malloc((length + 1) * sizeof(char));
                    snprintf(to_check, length + 1, "%d%s", iterations, dict[i]);
                    char *md5 = (char *)malloc(33 * sizeof(char));
                    str2md5(to_check, strlen(to_check), md5);
                    found = check_password_match(passwords, md5);
                    if (found >= 0)
                    {
                        pthread_mutex_lock(broken_mutex);
                        broken[found] = true;
                        pthread_mutex_unlock(broken_mutex);
                        pthread_mutex_lock(found_mutex);
                        (*n)++;
                        pthread_cond_signal(found_cond_var);
                        pthread_mutex_unlock(found_mutex);
                    }
                    free(md5);
                    free(to_check);
                }
            }
            if (h == 0)
                iterations++;

            if (h == 1)
                h = 0;
            else
                h = 1;
        }
        pthread_exit(NULL);
    }
}

void *produce2(void *arg)
{
    int tid, dict_entries;
    threadData *data;
    data = (threadData *)arg;
    tid = data->threadID;
    char **dict = data->dictionary;
    dict_entries = data->dictionary_entries;
    pthread_mutex_t *broken_mutex = data->broken_table_mutex;
    pthread_mutex_t *found_mutex = data->found_cond_var_mutex;
    pthread_cond_t *found_cond_var = data->found_cond_var;
    int *n = data->n;
    bool *end_flag = data->end_flag;

    sigset_t set;
    sigaddset(&set, SIGHUP);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    if (tid == 1) //first uppercase, other lowercase
    {
        int iterations = 0;
        int found = -1;
        int h = 0;
        while ((*end_flag) == false)
        {
            for (int i = 0; i < dict_entries; ++i)
            {
                if (iterations == 0)
                {
                    int length = strlen(dict[i]);
                    char *to_check = (char *)malloc((length + 1) * sizeof(char));
                    strcpy(to_check, dict[i]);
                    to_check[0] = toupper(to_check[0]);
                    char *md5 = (char *)malloc(33 * sizeof(char));
                    str2md5(to_check, strlen(to_check), md5);
                    found = check_password_match(passwords, md5);
                    if (found >= 0)
                    {
                        pthread_mutex_lock(broken_mutex);
                        broken[found] = true;
                        pthread_mutex_unlock(broken_mutex);
                        pthread_mutex_lock(found_mutex);
                        (*n)++;
                        pthread_cond_signal(found_cond_var);
                        pthread_mutex_unlock(found_mutex);
                    }
                    free(md5);
                    free(to_check);
                }
                else if (h == 0)
                {
                    int length = snprintf(NULL, 0, "%s%d", dict[i], iterations);
                    char *to_check = (char *)malloc((length + 1) * sizeof(char));
                    char *tmp = malloc((strlen(dict[i]) + 1) * sizeof(char));
                    strcpy(tmp, dict[i]);
                    tmp[0] = toupper(tmp[0]);
                    snprintf(to_check, length + 1, "%s%d", tmp, iterations);
                    char *md5 = (char *)malloc(33 * sizeof(char));
                    str2md5(to_check, strlen(to_check), md5);
                    found = check_password_match(passwords, md5);
                    if (found >= 0)
                    {
                        pthread_mutex_lock(broken_mutex);
                        broken[found] = true;
                        pthread_mutex_unlock(broken_mutex);
                        pthread_mutex_lock(found_mutex);
                        (*n)++;
                        pthread_cond_signal(found_cond_var);
                        pthread_mutex_unlock(found_mutex);
                    }
                    free(tmp);
                    free(md5);
                    free(to_check);
                }
                else if (h == 1)
                {
                    int length = snprintf(NULL, 0, "%d%s", iterations, dict[i]);
                    char *to_check = (char *)malloc((length + 1) * sizeof(char));
                    char *tmp = malloc((strlen(dict[i]) + 1) * sizeof(char));
                    strcpy(tmp, dict[i]);
                    tmp[0] = toupper(tmp[0]);
                    snprintf(to_check, length + 1, "%d%s", iterations, tmp);
                    char *md5 = (char *)malloc(33 * sizeof(char));
                    str2md5(to_check, strlen(to_check), md5);
                    found = check_password_match(passwords, md5);
                    if (found >= 0)
                    {
                        pthread_mutex_lock(broken_mutex);
                        broken[found] = true;
                        pthread_mutex_unlock(broken_mutex);
                        pthread_mutex_lock(found_mutex);
                        (*n)++;
                        pthread_cond_signal(found_cond_var);
                        pthread_mutex_unlock(found_mutex);
                    }
                    free(tmp);
                    free(md5);
                    free(to_check);
                }
            }
            if (h == 0)
                iterations++;

            if (h == 1)
                h = 0;
            else
                h = 1;
        }
        pthread_exit(NULL);
    }
}

void *produce3(void *arg)
{
    int tid, dict_entries;
    threadData *data;
    data = (threadData *)arg;
    tid = data->threadID;
    char **dict = data->dictionary;
    dict_entries = data->dictionary_entries;
    pthread_mutex_t *broken_mutex = data->broken_table_mutex;
    pthread_mutex_t *found_mutex = data->found_cond_var_mutex;
    pthread_cond_t *found_cond_var = data->found_cond_var;
    int *n = data->n;
    bool *end_flag = data->end_flag;

    sigset_t set;
    sigaddset(&set, SIGHUP);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    if (tid == 2) // all uppercase
    {
        int iterations = 0;
        int found = -1;
        int h = 0;
        while ((*end_flag) == false)
        {
            for (int i = 0; i < dict_entries; ++i)
            {
                if (iterations == 0)
                {
                    int length = strlen(dict[i]);
                    char *to_check = (char *)malloc((length + 1) * sizeof(char));
                    str2uppercase(dict[i], length, to_check);
                    char *md5 = (char *)malloc(33 * sizeof(char));
                    str2md5(to_check, length, md5);
                    found = check_password_match(passwords, md5);
                    if (found >= 0)
                    {
                        pthread_mutex_lock(broken_mutex);
                        broken[found] = true;
                        pthread_mutex_unlock(broken_mutex);
                        pthread_mutex_lock(found_mutex);
                        (*n)++;
                        pthread_cond_signal(found_cond_var);
                        pthread_mutex_unlock(found_mutex);
                    }
                    free(md5);
                    free(to_check);
                }
                else if (h == 0)
                {
                    int length = snprintf(NULL, 0, "%s%d", dict[i], iterations);
                    char *to_check = (char *)malloc((length + 1) * sizeof(char));
                    char *tmp = malloc((strlen(dict[i]) + 1) * sizeof(char));
                    strcpy(tmp, dict[i]);
                    str2uppercase(tmp, strlen(tmp), tmp);
                    snprintf(to_check, length + 1, "%s%d", tmp, iterations);
                    char *md5 = (char *)malloc(33 * sizeof(char));
                    str2md5(to_check, strlen(to_check), md5);
                    found = check_password_match(passwords, md5);
                    if (found >= 0)
                    {
                        pthread_mutex_lock(broken_mutex);
                        broken[found] = true;
                        pthread_mutex_unlock(broken_mutex);
                        pthread_mutex_lock(found_mutex);
                        (*n)++;
                        pthread_cond_signal(found_cond_var);
                        pthread_mutex_unlock(found_mutex);
                    }
                    free(tmp);
                    free(md5);
                    free(to_check);
                }
                else if (h == 1)
                {
                    int length = snprintf(NULL, 0, "%d%s", iterations, dict[i]);
                    char *to_check = (char *)malloc((length + 1) * sizeof(char));
                    char *tmp = malloc((strlen(dict[i]) + 1) * sizeof(char));
                    strcpy(tmp, dict[i]);
                    str2uppercase(tmp, strlen(tmp), tmp);
                    snprintf(to_check, length + 1, "%d%s", iterations, tmp);
                    char *md5 = (char *)malloc(33 * sizeof(char));
                    str2md5(to_check, strlen(to_check), md5);
                    found = check_password_match(passwords, md5);
                    if (found >= 0)
                    {
                        pthread_mutex_lock(broken_mutex);
                        broken[found] = true;
                        pthread_mutex_unlock(broken_mutex);
                        pthread_mutex_lock(found_mutex);
                        (*n)++;
                        pthread_cond_signal(found_cond_var);
                        pthread_mutex_unlock(found_mutex);
                    }
                    free(tmp);
                    free(md5);
                    free(to_check);
                }
            }
            if (h == 0)
                iterations++;

            if (h == 1)
                h = 0;
            else
                h = 1;
        }
        pthread_exit(NULL);
    }
}

void *produce_double1(void *arg)
{
    int tid, dict_entries;
    threadData *data;
    data = (threadData *)arg;
    tid = data->threadID;
    char **dict = data->dictionary;
    dict_entries = data->dictionary_entries;
    pthread_mutex_t *broken_mutex = data->broken_table_mutex;
    pthread_mutex_t *found_mutex = data->found_cond_var_mutex;
    pthread_cond_t *found_cond_var = data->found_cond_var;
    int *n = data->n;
    bool *end_flag = data->end_flag;
    int iterations = 0;
    int found = -1;
    int h = 0;

    sigset_t set;
    sigaddset(&set, SIGHUP);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    while ((*end_flag) == false)
    {
        for (int i = 0; (i < dict_entries) && ((*end_flag) == false); ++i)
        {
            for (int j = 0; j < (dict_entries - i - 1); ++j)
            {
                int length1 = strlen(dict[i]);
                int length2 = strlen(dict[i + j]);
                char *to_check = (char *)malloc((length1 + length2 + 1) * sizeof(char));
                strcpy(to_check, dict[i]);
                strcat(to_check, dict[i + j]);
                char *md5 = (char *)malloc(33 * sizeof(char));
                str2md5(to_check, length1 + length2, md5);
                found = check_password_match(passwords, md5);
                if (found >= 0)
                {
                    pthread_mutex_lock(broken_mutex);
                    broken[found] = true;
                    pthread_mutex_unlock(broken_mutex);
                    pthread_mutex_lock(found_mutex);
                    (*n)++;
                    pthread_cond_signal(found_cond_var);
                    pthread_mutex_unlock(found_mutex);
                }
                free(md5);
                free(to_check);
                //free(tmp);
            }
        }
    }
    pthread_exit(NULL);
}

void *produce_double2(void *arg)
{
    int tid, dict_entries;
    threadData *data;
    data = (threadData *)arg;
    tid = data->threadID;
    char **dict = data->dictionary;
    dict_entries = data->dictionary_entries;
    pthread_mutex_t *broken_mutex = data->broken_table_mutex;
    pthread_mutex_t *found_mutex = data->found_cond_var_mutex;
    pthread_cond_t *found_cond_var = data->found_cond_var;
    int *n = data->n;
    bool *end_flag = data->end_flag;
    int iterations = 0;
    int found = -1;
    int h = 0;

    sigset_t set;
    sigaddset(&set, SIGHUP);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    while ((*end_flag) == false)
    {
        for (int i = 0; (i < dict_entries) && ((*end_flag) == false); ++i)
        {
            for (int j = 0; j < (dict_entries - i - 1); ++j)
            {
                int length1 = strlen(dict[i]);
                int length2 = strlen(dict[i + j]);
                char *to_check = (char *)malloc((length1 + length2 + 1) * sizeof(char));
                strcpy(to_check, dict[i]);
                strcat(to_check, dict[i + j]);
                char *tmp = (char *)malloc((strlen(to_check) + 1) * sizeof(char));
                str2uppercase(to_check, length1 + length2, tmp);
                char *md5 = (char *)malloc(33 * sizeof(char));
                str2md5(tmp, length1 + length2, md5);
                found = check_password_match(passwords, md5);
                if (found >= 0)
                {
                    pthread_mutex_lock(broken_mutex);
                    broken[found] = true;
                    pthread_mutex_unlock(broken_mutex);
                    pthread_mutex_lock(found_mutex);
                    (*n)++;
                    pthread_cond_signal(found_cond_var);
                    pthread_mutex_unlock(found_mutex);
                }
                free(md5);
                free(to_check);
                free(tmp);
            }
        }
    }
    pthread_exit(NULL);
}