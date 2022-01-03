#ifndef PRODUCER_H_
#define PRODUCER_H_

#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include "StringConversion.h"

void *produce1(void *arg);

void *produce2(void *arg);

void *produce3(void *arg);

void *produce_double1(void *arg);

void *produce_double2(void *arg);
#endif