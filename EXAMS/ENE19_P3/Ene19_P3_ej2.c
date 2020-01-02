#include <sys/types.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#define SUCCESS 0
#define FAILURE 1

volatile int n_sigint = 0;
volatile int n_sigstp = 0;

void handler(int n){
	if(n == SIGINT){
		n_sigint = n_sigint + 1;
		printf("SIGINT ocurred\n");
	}
	if(n == SIGTSTP){
		n_sigstp = n_sigstp + 1;
		printf("SIGTSTP ocurred\n");
	}
}

int main(int argc, char ** argv){
	struct sigaction act;
	
	memset(&act, 0, sizeof(struct sigaction));
	act.sa_handler = &handler;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGINT);
	sigaddset(&act.sa_mask, SIGTSTP);

	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGTSTP, &act, NULL);

	while(n_sigint + n_sigstp < 10)
		;

	printf("Recibidas %d señales SIGINT\n", n_sigint);
	printf("Recibidas %d señales SIGTSTP\n", n_sigstp);	

	return SUCCESS;
}
