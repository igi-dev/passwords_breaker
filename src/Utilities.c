#include "Utilities.h"

void init_passwords_table(char *filename, int size)
{
    read_passwords(filename, size, passwords);
    for (int i = 0; i < PASSWORDS; ++i)
    {
        broken[i] = false;
    }
}

void init_dictionary(char **dict, int lines_count, char *filename)
{
    char *tmp;
    FILE *file;
    file = fopen(filename, "r");
    char *buffer;
    size_t buffersize = 24;
    size_t characters = 1;
    int i = 0;
    buffer = (char *)malloc(buffersize * sizeof(char));
    if (buffer == NULL)
    {
        printf("ERROR, unable to allocate buffer!");
        return;
    }
    while (characters > 0 && i < lines_count)
    {
        characters = getline(&buffer, &buffersize, file);
        dict[i] = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        if (dict[i] == NULL)
        {
            printf("ERROR, unable to allocate memory for dictionary line!");
            return;
        }
        buffer[strlen(buffer) - 1] = '\0'; // trick to remove \n at the end of the buffer
        memcpy(dict[i], buffer, characters);
        i++;
    }
    free(buffer);
    fclose(file);
}

void free_dictionary(char **dict, int lines_count)
{
    for (int i = 0; i < lines_count; i++)
    {
        free(dict[i]);
    }
}

void read_passwords(char *name, int size, char output_array[][33])
{
    FILE *file;
    file = fopen(name, "r");
    if (file == NULL)
    {
        printf("passwords file error!");
        return;
    }
    char *buffer;
    size_t buffersize = 32;
    size_t characters = 1;
    int i = 0;
    buffer = (char *)malloc((buffersize+1) * sizeof(char));
    if (buffer == NULL)
    {
        printf("ERROR, unable to allocate buffer!");
        return;
    }
    for (int i = 0; i < PASSWORDS; i++)
    {
        getline(&buffer,&buffersize,file);
        memcpy(output_array[i],buffer,32);
    }
    free(buffer);
    fclose(file);
}

int countlines(char *filename)
{

    FILE *fp = fopen(filename, "r");

    if (!fp)
    {
        fprintf(stderr, "Error in opening file");
        return 0;
    }

    int count = 1; //if a file open ,be it empty, it has atleast a newline char
    char temp;

    while (fscanf(fp, "%c", &temp) != -1)
    {
        if (temp == 10)
            count++;
    }
    fclose(fp);
    return count;
}

int check_password_match(char passwords_table[][33], char *md5_str)
{
    for (int i = 0; i < PASSWORDS; ++i)
    {
        if (broken[i] != true)
        {
            if (strcmp(passwords_table[i], md5_str) == 0)
            {
                return i;
            }
        }
    }
    return -1;
}