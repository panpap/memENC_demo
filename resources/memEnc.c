#include "header.h"
#include <openssl/evp.h>
#include <wmmintrin.h>  //for AES-NI intrinsics 

#define SHM_KEY 13424242
#define CLEAR_SCREEN_ANSI "\e[1;1H\e[2J"

#define DO_ENC_BLOCK(m,k) \
	do{\
        m = _mm_xor_si128       (m, k[ 0]); \
        m = _mm_aesenc_si128    (m, k[ 1]); \
        m = _mm_aesenc_si128    (m, k[ 2]); \
        m = _mm_aesenc_si128    (m, k[ 3]); \
        m = _mm_aesenc_si128    (m, k[ 4]); \
        m = _mm_aesenc_si128    (m, k[ 5]); \
        m = _mm_aesenc_si128    (m, k[ 6]); \
        m = _mm_aesenc_si128    (m, k[ 7]); \
        m = _mm_aesenc_si128    (m, k[ 8]); \
        m = _mm_aesenc_si128    (m, k[ 9]); \
        m = _mm_aesenclast_si128(m, k[10]);\
    }while(0)

#define DO_DEC_BLOCK(m,k) \
	do{\
        m = _mm_xor_si128       (m, k[10+0]); \
        m = _mm_aesdec_si128    (m, k[10+1]); \
        m = _mm_aesdec_si128    (m, k[10+2]); \
        m = _mm_aesdec_si128    (m, k[10+3]); \
        m = _mm_aesdec_si128    (m, k[10+4]); \
        m = _mm_aesdec_si128    (m, k[10+5]); \
        m = _mm_aesdec_si128    (m, k[10+6]); \
        m = _mm_aesdec_si128    (m, k[10+7]); \
        m = _mm_aesdec_si128    (m, k[10+8]); \
        m = _mm_aesdec_si128    (m, k[10+9]); \
        m = _mm_aesdeclast_si128(m, k[0]);\
    }while(0)

#define AES_128_key_exp(k, rcon) aes_128_key_expansion(k, _mm_aeskeygenassist_si128(k, rcon))

void aes128_load_key(int8_t *enc_key);
static __m128i aes_128_key_expansion(__m128i key, __m128i keygened);
void aes128_enc(int8_t *plainText,int8_t *cipherText);
void aes128_dec(int8_t *cipherText,int8_t *plainText);
int8_t enc_key[]    = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
static __m128i key_schedule[20];//the expanded key


void exitNicely(char *buffer){
	printf("memenc closed\n");
	shmdt(buffer);
}

char *readCmd(const char *line){
	char s[256], s2[256];
	strcpy(s, line);
	strcpy(s2, line);
	char* cmd = strtok(s, " ");
	if (strcmp(cmd,"insert")!=0)
		return NULL;
	strtok(s2, "\"");
	char* value = strtok(NULL, "\""); //get second part
	return strdup(value);
}

char *saveVal(char *plain,char *shared_buffer){//memenc
	int8_t computed_cipher[STRING_SIZE];int c=0;
	int pos=rand()%SLOTS_SIZE;
printf("%s %d\n",plain,pos);
	if (shared_buffer==NULL)
		shared_buffer = create_shared_mem_buffer();
	aes128_load_key(enc_key);
	aes128_enc((int8_t *)plain,computed_cipher);

	for (c=pos*STRING_SIZE; c < pos*STRING_SIZE+strlen((char *)computed_cipher); c++)
		shared_buffer[c]=computed_cipher[c-(pos*STRING_SIZE)];
	printf("\nSECURELY INSERTED %d\n",pos);
	return shared_buffer;
}


void decryptANDprint(int8_t *word){
	int8_t computed_plain[STRING_SIZE];
	if (strlen((char*)word)>2){
		aes128_dec(word,computed_plain);
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
					BIO_dump_fp (stdout, (const char *)word, sizeof(word));
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
					printf("%02X [%d]", word[c],c);
			}
		}
		c++;
  }
  printf("\n--------\n");
}


char *create_shared_mem_buffer() {	
	char *shmaddr=NULL;
    int shmid;
  	key_t key = SHM_KEY;
	if ((shmid = shmget(key, SLOTS_SIZE*STRING_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    } 
    if ((shmaddr = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }
  	return shmaddr;
}

void clear_buffer(char *sbuff,long size) {
  int i = 0;
  for (i = 0; i < size; ++i) 
		sbuff[i] = 0x00;
}


static __m128i aes_128_key_expansion(__m128i key, __m128i keygened){
	keygened = _mm_shuffle_epi32(keygened, _MM_SHUFFLE(3,3,3,3));
	key = _mm_xor_si128(key, _mm_slli_si128(key, 4));
	key = _mm_xor_si128(key, _mm_slli_si128(key, 4));
	key = _mm_xor_si128(key, _mm_slli_si128(key, 4));
	return _mm_xor_si128(key, keygened);
}

//public API
void aes128_load_key(int8_t *enc_key){
    key_schedule[0] = _mm_loadu_si128((const __m128i*) enc_key);
	key_schedule[1]  = AES_128_key_exp(key_schedule[0], 0x01);
	key_schedule[2]  = AES_128_key_exp(key_schedule[1], 0x02);
	key_schedule[3]  = AES_128_key_exp(key_schedule[2], 0x04);
	key_schedule[4]  = AES_128_key_exp(key_schedule[3], 0x08);
	key_schedule[5]  = AES_128_key_exp(key_schedule[4], 0x10);
	key_schedule[6]  = AES_128_key_exp(key_schedule[5], 0x20);
	key_schedule[7]  = AES_128_key_exp(key_schedule[6], 0x40);
	key_schedule[8]  = AES_128_key_exp(key_schedule[7], 0x80);
	key_schedule[9]  = AES_128_key_exp(key_schedule[8], 0x1B);
	key_schedule[10] = AES_128_key_exp(key_schedule[9], 0x36);

	// generate decryption keys in reverse order.
    // k[10] is shared by last encryption and first decryption rounds
    // k[0] is shared by first encryption round and last decryption round (and is the original user key)
    // For some implementation reasons, decryption key schedule is NOT the encryption key schedule in reverse order
	key_schedule[11] = _mm_aesimc_si128(key_schedule[9]);
	key_schedule[12] = _mm_aesimc_si128(key_schedule[8]);
	key_schedule[13] = _mm_aesimc_si128(key_schedule[7]);
	key_schedule[14] = _mm_aesimc_si128(key_schedule[6]);
	key_schedule[15] = _mm_aesimc_si128(key_schedule[5]);
	key_schedule[16] = _mm_aesimc_si128(key_schedule[4]);
	key_schedule[17] = _mm_aesimc_si128(key_schedule[3]);
	key_schedule[18] = _mm_aesimc_si128(key_schedule[2]);
	key_schedule[19] = _mm_aesimc_si128(key_schedule[1]);
}

void aes128_enc(int8_t *plainText,int8_t *cipherText){
    __m128i m = _mm_loadu_si128((__m128i *) plainText);
    DO_ENC_BLOCK(m,key_schedule);
    _mm_storeu_si128((__m128i *) cipherText, m);
}

void aes128_dec(int8_t *cipherText,int8_t *plainText){
    __m128i m = _mm_loadu_si128((__m128i *) cipherText);
    DO_DEC_BLOCK(m,key_schedule);
    _mm_storeu_si128((__m128i *) plainText, m);
}
