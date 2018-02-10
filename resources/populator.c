#include "header.h"

char *plainVal(char plain[],char *shared_buffer) {
	int pos=rand()%SLOTS_SIZE;
printf("%d\n",pos);
	if (shared_buffer==NULL)
  		shared_buffer = create_shared_mem_buffer();
	int c=0;
   	for (c=pos*STRING_SIZE; c < pos*STRING_SIZE+strlen(plain); c++)
    	shared_buffer[c]=plain[c-(pos*STRING_SIZE)];
	printf("\nINSERTED %d %s\n",pos, plain);
	return shared_buffer;
}


int main(int argc, const char *argv[])
{
	time_t t;srand((unsigned) time(&t));
	char plain[]="Hello World!\0",plain2[]="Panos";
	char *shared_buffer=NULL;
	if((argv[1]!=NULL) && (atoi(argv[1])==1)){
		printf("SECURE STORE\n");
		shared_buffer=saveVal(plain,shared_buffer);
		sleep(2);
		shared_buffer=saveVal(plain2,shared_buffer);
	}else{
		shared_buffer=plainVal(plain,shared_buffer);
		sleep(2);
		shared_buffer=plainVal(plain2,shared_buffer);
	}
	shmdt(shared_buffer);
	return EXIT_SUCCESS;
}
