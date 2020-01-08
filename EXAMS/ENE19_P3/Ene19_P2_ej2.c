#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


volatile int n_sigint = 0;
volatile int n_sigstp = 0;

static void handler(int sig, siginfo_t *si, void *unused){
        if(si->si_signo == SIGINT)
                n_sigint = n_sigint + 1;
        if(si->si_signo == SIGTSTP)
                n_sigstp = n_sigstp + 1;

        if(n_sigint + n_sigstp == 10){
                printf("Received %d SIGINT and %d SIGTSTP\n", n_sigint, n_sigstp);
                exit(EXIT_SUCCESS);
        }
}

int main(int argc, char ** argv){
        struct sigaction sa;

        memset(&sa, 0, sizeof(struct sigaction));


        sa.sa_flags = SA_SIGINFO;

        sigemptyset(&sa.sa_mask);
        sigaddset(&sa.sa_mask, SIGINT);
        sigaddset(&sa.sa_mask, SIGTSTP);

        sa.sa_sigaction = &handler;
        if(sigaction(SIGINT, &sa, NULL) < 0)
                exit(EXIT_FAILURE);

        if(sigaction(SIGTSTP, &sa, NULL) < 0)
                exit(EXIT_FAILURE);

        while(1)
                ;

        return EXIT_SUCCESS;
}