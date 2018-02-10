#include "header.h"

int main(int argc, const char *argv[])
{
  	char *shared_buffer = create_shared_mem_buffer();
	if ((argv[2]!=NULL) && (atoi(argv[2])==1))
		clear_buffer(shared_buffer,SLOTS_SIZE*STRING_SIZE);
	int decrypt=0;
	if ((argv[1]!=NULL) && (atoi(argv[1])==1))
	{
		printf("VERIFY CIPHERTEXT\n");
		decrypt=1;
	}
  	while(1) {
    	monitorMem(shared_buffer,decrypt);
		sleep(1);
  	} 
  	return EXIT_SUCCESS;
}
