#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>

int main(void)
{
	void  sigint_handler(int sig);
	char s[200];
	
	if (signal(SIGINT, sigint_handler) == SIG_ERR || signal(SIGTSTP, sigint_handler) == SIG_ERR || signal(SIGQUIT, sigint_handler) == SIG_ERR){
        perror("signal");
        exit(1);
        }
	printf("Enter a string:\n");
	if (fgets(s,200,stdin) == NULL)
		perror("stop: ");
	else
		printf("you entered : %s\n",s);
	return 0;
}

void sigint_handler(int sig)
{
	if (sig == SIGINT)
		printf("This is signal for SIGINT\n");
	else if (sig == SIGTSTP)
		printf("This is signal for SIGTSTP\n");
	else
		printf("This is signal for SIGQUIT\n");
}
