#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


#define SUCCESS 0
#define FAILURE 1


int main(int argc, char ** argv){
	int pid, fd, fd_dup, status;

	pid = fork();
	if(pid < 0){
		perror("fork() ERROR\n");
		exit(-FAILURE);
	}
	else if(pid > 0){	/* child */
		printf("Process ID	= %d\n", getpid());
		fd_dup = dup2(2, fd);
		close(fd);
		execl(argv[1], argv[1], 0);
	}
	else{			/* parent */
		printf("Process ID	= %d\n", getpid());
		fd_dup = dup2(fd, 1);
		close(fd);
		execv(argv[2], argv + 2);
		wait(&status);		/* waits for children finish */

	}


	return SUCCESS;
}
