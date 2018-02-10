#ifndef HEADER_H_
#define HEADER_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <errno.h>

#define SLOTS_SIZE 5
#define STRING_SIZE 30
char *create_shared_mem_buffer();
void clear_buffer(char *sbuff,long size);
void debug_buffer(char *sbuff, int decrypt);
char *readCmd(const char *);
char *saveVal(char *,char *);
void exitNicely(char *);
#endif
