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

#define SLOTS_SIZE 20
#define STRING_SIZE 16 //one AES block
char *create_shared_mem_buffer();
void clear_buffer(char *sbuff,long size);
void monitorMem(char *sbuff, int decrypt);
char *readCmd(const char *);
char *saveVal(char *,char *);
char *plainVal(char *,char *);
void exitNicely(char *);
#endif
