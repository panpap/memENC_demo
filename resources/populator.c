#include "../resources/header.h"

char *saveVal(int pos,int8_t plain[]) {
	int8_t computed_cipher[STRING_SIZE];
	if ((pos>SLOTS_SIZE) || (pos<0)) return NULL;
  	char *shared_buffer = create_shared_mem_buffer();
    aes128_load_key(enc_key);
    aes128_enc(plain,computed_cipher);
	int c=0;pos--;
   	for (c=pos*STRING_SIZE; c < pos*STRING_SIZE+strlen((char *)computed_cipher); c++)
    	shared_buffer[c]=computed_cipher[c-(pos*STRING_SIZE)];
	printf("\nSECURELY INSERTED\n");
	return shared_buffer;
}

char *plainVal(int pos,int8_t plain[]) {
	if ((pos>SLOTS_SIZE) || (pos<0)) return NULL;
  	char *shared_buffer = create_shared_mem_buffer();
	int c=0;pos--;
   	for (c=pos*STRING_SIZE; c < pos*STRING_SIZE+strlen((char *)plain); c++)
    	shared_buffer[c]=plain[c-(pos*STRING_SIZE)];
	printf("INSERTED\n");
	return shared_buffer;
}


int main(int argc, const char *argv[])
{
	int8_t plain[]="Hello World!",plain2[]="Panos";
	char *shared_buffer;
	if((argv[1]!=NULL) && (atoi(argv[1])==1)){
		printf("SECURE STORE\n");
		shared_buffer=saveVal(5,plain);
		sleep(2);
		shared_buffer=saveVal(2,plain2);
	}else{
		shared_buffer=plainVal(5,plain);
		sleep(2);
		shared_buffer=plainVal(2,plain2);
	}
	shmdt(shared_buffer);
	return EXIT_SUCCESS;
}
