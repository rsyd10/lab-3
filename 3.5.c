#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

void sigint_handler(int sig){
	printf("Sorry, can't do\n");
}


int main(void) {
	int pipefds[2];
	int number;
	int buffer;

	if(signal(SIGINT, sigint_handler) == SIG_ERR){
                perror("signal");
                exit(1);
	}

	if(pipe(pipefds) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid_t pid = fork();

	if(pid == 0) {
		int number;
		printf("Please enter a number : ");
		scanf("%d", &number);
		close(pipefds[0]);
		write(pipefds[1], &number, sizeof(number));
		printf("Passing to parents for checking\n");
		exit(EXIT_SUCCESS);
	}
	else if(pid > 0){
		printf("Passing to child process\n");
		wait(NULL);
		close(pipefds[1]);
		read(pipefds[0], &buffer, sizeof(buffer));
		close(pipefds[0]);
		printf("The number %d ", buffer);
		if(buffer > 3) {
			for (int i=2; i<= buffer/2; i++)
			{
				if(buffer % i == 0)
				{
					printf("is not a prime number\n");
					exit(EXIT_SUCCESS);
				}
				else
				{
					printf("is a prime number\n");
					exit(EXIT_SUCCESS);
				}
			printf("Done.\n\n");
			}
		}
		else{
			if(buffer == 1)
				printf("is not  a prime number\n");
			else
				printf("Is a prime number\n");
		} 

		printf("Done.\n\n");
	}
	else
		perror("Error");
	return EXIT_SUCCESS;
}
