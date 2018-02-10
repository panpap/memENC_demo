#include "../resources/header.h"

char *shared_buffer;
char *saveVal(int8_t plain[]) {
	int8_t computed_cipher[STRING_SIZE];
	time_t t;
	srand((unsigned) time(&t));
	int pos=rand()%SLOTS_SIZE;
  	shared_buffer = create_shared_mem_buffer();
    aes128_load_key(enc_key);
    aes128_enc(plain,computed_cipher);
	int c=0;pos--;
   	for (c=pos*STRING_SIZE; c < pos*STRING_SIZE+strlen((char *)computed_cipher); c++)
    	shared_buffer[c]=computed_cipher[c-(pos*STRING_SIZE)];
	printf("\nSECURELY INSERTED %d\n",pos);
	return shared_buffer;
}

char *plainVal(int8_t plain[]) {
	time_t t;
	srand((unsigned) time(&t));
	int pos=rand()%SLOTS_SIZE;
printf("%d\n",pos);
  	char *shared_buffer = create_shared_mem_buffer();
	int c=0;pos--;
   	for (c=pos*STRING_SIZE; c < pos*STRING_SIZE+strlen((char *)plain); c++)
    	shared_buffer[c]=plain[c-(pos*STRING_SIZE)];
	printf("\nINSERTED %d\n",pos);
	return shared_buffer;
}


int main(int argc, const char *argv[])
{
	int8_t plain[]="Hello World!",plain2[]="Panos";
	if((argv[1]!=NULL) && (atoi(argv[1])==1)){
		printf("SECURE STORE\n");
		shared_buffer=saveVal(plain);
		sleep(2);
		shared_buffer=saveVal(plain2);
	}else{
		shared_buffer=plainVal(plain);
		sleep(2);
		shared_buffer=plainVal(plain2);
	}
	shmdt(shared_buffer);
	return EXIT_SUCCESS;
}
