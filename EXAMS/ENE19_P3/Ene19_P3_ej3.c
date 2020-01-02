#include <sys/types.h>
#include <sys/stat.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE 1
#define BUFSIZE 128
#define MAXCONN 10


int main(int argc, char ** argv){
	struct sockaddr_storage cli;
	socklen_t clilen, servlen;
	struct addrinfo hints, *result;
	int len, pid, connect_sd, listen_sd;
	char *buf, *host, *port;

	if(memset(&hints, 0, sizeof(struct addrinfo)) < 0){
		perror("memeset() ERROR\n");
		exit(-FAILURE);
	}

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if(getaddrinfo(argv[1], argv[2], &hints, &result) < 0){
		perror("getaddrinfo() ERROR\n");
		exit(-FAILURE);
	}

	servlen = result->ai_addrlen;

	if((listen_sd = socket(result->ai_family, result->ai_socktype, 0)) < 0){
		perror("socket() ERROR\n");
		exit(-FAILURE);
	}

	if(bind(listen_sd, (struct sockaddr*) result->ai_addr, servlen) < 0){
		perror("bind() ERROR\n");
		exit(-FAILURE);
	}

	if(listen(listen_sd, MAXCONN) < 0){
		perror("listen() ERROR\n");
		exit(-FAILURE);
	}

	while(1){
		buf = malloc(BUFSIZE);
		host = malloc(BUFSIZE);
		port = malloc(BUFSIZE);

		if((connect_sd = accept(listen_sd, (struct sockaddr*) &cli, &clilen)) < 0){
			perror("accept() ERROR\n");
			exit(-FAILURE);
		}

		if(getnameinfo((struct sockaddr*)&cli, clilen, host, BUFSIZE, port, BUFSIZE, 0) < 0){
			perror("getnameinfo() ERROR\n");
			exit(-FAILURE);
		}

		pid = fork();
		if(pid < 0){
			perror("fork() ERROR\n");
			exit(-FAILURE);
		}
		else if(pid == 0){
			close(listen_sd);
			
			while((len = read(connect_sd, buf, BUFSIZE)) > 0){
				buf[len] = '\0';
				write(connect_sd, buf, strlen(buf));
				printf("Process ID	= %d\n", getpid());
				printf("Client Address	= %s\n", host);
				printf("Client Port	= %s\n", port);
				free(buf);
				buf = malloc(BUFSIZE);
			}

			close(connect_sd);
			exit(SUCCESS);
		}

		free(buf);
		free(host);
		free(port);
	}

	return SUCCESS;
}
