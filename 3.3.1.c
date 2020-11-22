#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(void){

	int pipefds[2];
	int buffer;

	if (pipe(pipefds) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	int number = 22;

	printf("Writing a number to pipe...\n");
	write(pipefds[1], &number, sizeof(number));
	printf("Done.\n\n");

	printf("Reading a number from pipe...\n");
	read(pipefds[0],& buffer, sizeof(buffer));
	printf("Done.\n\n");

	printf("Number from pipe: %d\n", buffer);
	return EXIT_SUCCESS;
}
