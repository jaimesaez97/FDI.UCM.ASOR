#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define SUCCESS 0
#define FAILURE 1


int main(int argc, char ** argv){
        int pid, p;

        pid = fork();
        if(pid < 0){
                perror("fork() ERROR\n");
                exit(-FAILURE);
        }
        else if (pid > 0)      /* parent */
                exit(SUCCESS);

        if(setsid() < 0)
                exit(-FAILURE);


        if(chdir("/tmp") < 0)
                exit(-FAILURE);

        if((p = getpid()) < 0)
                exit(-FAILURE);

        printf("Process ID      = %d\n", p);

        if((p = getppid()) < 0)
                exit(-FAILURE);

        printf("Parent ID       = %d\n", p);

        if((p = getgid()) < 0)
                exit(-FAILURE);

        printf("Group ID        = %d\n", p);

        if((p = getsid(getpid())) < 0)
                exit(-FAILURE);

        printf("Session ID      = %d\n", p);

        execv(argv[1], argv+1);

        return SUCCESS;
}
