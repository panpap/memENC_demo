#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define SLOTS_SIZE 5
#define EMPTY_ID 0
#define FULL_ID 1
#define MUTEX_ID 2
#define NSEM_SIZE 3
#define STRING_SIZE 30
#define SHM_KEY 91
#define SEM_KEY "."

static struct sembuf downEmpty = { EMPTY_ID, -1, 0 };
static struct sembuf upEmpty = { EMPTY_ID, 1, 0 };
static struct sembuf upFull = { FULL_ID, 1, 0 };
static struct sembuf downFull = { FULL_ID, -1, 0 };
static struct sembuf downMutex = { MUTEX_ID, -1, 0 };
static struct sembuf upMutex = { MUTEX_ID, 1, 0 };

char *create_shared_mem_buffer();
int create_semaphore_set();
//int get_buffer_size(char *sbuff);
//void clear_buffer(char *sbuf);
void debug_buffer(char *sbuff);

/**
 * returns current size of shared buffer
 *
int get_buffer_size(char **sbuff) {
  int i = 0;
  int counter = 0;
  for (i = 0; i < SLOTS_SIZE; ++i) {
    if (sbuff[i] == 0xFF) {
      counter++;
    } 
  }
  return counter;
}*/

void debug_buffer(char *sbuff) {
  int i = 0;
	printf("MEMORY CONTENTS\n--------\n");
  for (i = 0; i < SLOTS_SIZE*STRING_SIZE; i++) {
		if (i%STRING_SIZE==0) printf("\n%d. ",i/STRING_SIZE);
		if (sbuff[i]!='\n') printf("%c",sbuff[i]);
  }
  printf("\n--------\n");
}

/**
 * returns a pointer to a shared memory buffer that the
 * producer can write to.
 */
char *create_shared_mem_buffer() {	
	char *shmaddr=NULL;
	long size=SLOTS_SIZE*STRING_SIZE; /* buffer address */
  	key_t key = SHM_KEY; /* use key to access a shared memory segment */
  	int shmid = shmget(key, size, IPC_CREAT | SHM_R | SHM_W); /* give create, read and write access */
  	if (errno > 0) {
    	printf("failed to create shared memory segment: %d\n",errno);
    	exit (EXIT_FAILURE);
  	}
  	shmaddr = (char*)shmat(shmid, NULL, 0);
  	if (errno > 0) {
  	  printf ("failed to attach to shared memory segment: %d\n",errno);
  	  exit (EXIT_FAILURE);
  	}
  	// clean out garbage memory in shared memory
  	return shmaddr;
}

/**
 * only used in the producer to clean out garbage memory when
 * constructing initial buffer.
 *
void clear_buffer(char **sbuff) {
  int i = 0;
  for (i = 0; i < BUFFER_SIZE; ++i) sbuff[i] = 0x00;
}*/

/**
 * create FULL and EMPTY semaphores
 */
int create_semaphore_set() {
  key_t key = ftok(SEM_KEY, 'E');
  
  int semid = semget(key, NSEM_SIZE, 0600 | IPC_CREAT);
  if (errno > 0) {
    perror("failed to create semaphore array");
    exit (EXIT_FAILURE);
  } 

  semctl(semid, FULL_ID, SETVAL, 0);
  if (errno > 0) {
    perror("failed to set FULL semaphore");
    exit (EXIT_FAILURE);
  }

  semctl(semid, EMPTY_ID, SETVAL, SLOTS_SIZE);
  if (errno > 0) {
    perror("failed to set EMPTY sempahore");
    exit (EXIT_FAILURE);
  }

  semctl(semid, MUTEX_ID, SETVAL, 1);
  if (errno > 0) {
    perror("failed to create mutex");
  }

  return semid;
}
