#include "header.h"

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
