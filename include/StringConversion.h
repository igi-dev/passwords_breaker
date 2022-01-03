
#ifndef CSTRING_CONVERSION_H_
#define CSTRING_CONVERSION_H_

#include <openssl/md5.h>
#include <openssl/evp.h>
#include <ctype.h>
#include "Utilities.h"

void str2md5(char *str, int length, char *output);

void str2uppercase(const char *input_string, const int length, char *output_string);

void bytes2md5(const char *data, int len, char *md5buf);

#endif