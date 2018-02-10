#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include "../resources/aes.h"

#define SLOTS_SIZE 5
#define NSEM_SIZE 3
#define STRING_SIZE 30
#define SHM_KEY 9190
#define SEM_KEY "."
#define CLEAR_SCREEN_ANSI "\e[1;1H\e[2J"


int8_t enc_key[]    = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
char *create_shared_mem_buffer();
int create_semaphore_set();
//int get_buffer_size(char *sbuff);
void clear_buffer(char *sbuff,long size);
void debug_buffer(char *sbuff, int decrypt);
void print_hex(unsigned char *, size_t);
/*
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

void
print_hex(unsigned char *data, size_t len)
{
	size_t i;

	if (!data)
		printf("NULL data\n");
	else {
		for (i = 0; i < len; i++) {
			//if (!(i % 16) && (i != 0))
			//	printf("\n");
			printf("%02X ", data[i]);
		}
		printf("\n");
	}
}

void decryptANDprint(int8_t *word){
	int8_t computed_plain[STRING_SIZE];
	if (strlen((char*)word)>2){
		aes128_dec(word,computed_plain);
		//print_hex((unsigned char *)computed_plain, STRING_SIZE);
		//printf("-> {%s}",computed_plain);
		BIO_dump_fp (stdout, (const char *)computed_plain, sizeof(word));
	}
	printf("\n");
}

void debug_buffer(char *sbuff, int decrypt) {
	int i = 0,c=0;
	aes128_load_key(enc_key);
	int8_t word[STRING_SIZE];
	printf(CLEAR_SCREEN_ANSI);
	if (decrypt==1)
		printf("BOB CAN SEE MEMORY CONTENTS (DECRYPTED):\n--------\n");
	else
		printf("EVE CAN SEE MEMORY CONTENTS:\n--------\n");
  	for (i = 0; i < SLOTS_SIZE*STRING_SIZE; i++) {
		if (i%STRING_SIZE==0) 
		{
			if (i!=0){
				if (decrypt)
					decryptANDprint(word);
				else
					//printf("%s\n",word);
					BIO_dump_fp (stdout, (const char *)word, sizeof(word));
//					print_hex((unsigned char *)word, STRING_SIZE);
			}
			printf("%d. ",i/STRING_SIZE);
			c=0;
			clear_buffer((char *)word,STRING_SIZE);
		}
		word[c]=sbuff[i];
		if (i/STRING_SIZE==SLOTS_SIZE-1){
			if (decrypt==1){
				if ((i+1)%STRING_SIZE==0)
					decryptANDprint(word);
			}else{
				if (word[c]!='\0')
					//printf("%c",word[c]);
					printf("%02X ", word[c]);
			}
		}
		c++;
  }
  printf("\n--------\n");
}


char *create_shared_mem_buffer() {	
	char *shmaddr=NULL;
  	key_t key = SHM_KEY; /* use key to access a shared memory segment */
  	int shmid = shmget(key, SLOTS_SIZE*STRING_SIZE, IPC_CREAT | SHM_R | SHM_W); /* give create, read and write access */
  	if (errno > 0) {
    	printf("failed to create shared memory segment: %d\n",errno);
    	exit (EXIT_FAILURE);
  	}
  	shmaddr = (char*)shmat(shmid, NULL, 0);
  	if (errno > 0) {
  	  printf ("failed to attach to shared memory segment: %d\n",errno);
  	  exit (EXIT_FAILURE);
  	}
  	return shmaddr;
}

void clear_buffer(char *sbuff,long size) {
  int i = 0;
  for (i = 0; i < size; ++i) 
		sbuff[i] = 0x00;
}

