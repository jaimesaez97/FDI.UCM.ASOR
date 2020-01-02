#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#define SUCCESS 0
#define FAILURE 1
#define BUFSIZE 128


int main(int argc, char ** argv){
        struct sockaddr_storage cli;
        socklen_t servlen, clilen;
        struct addrinfo hints, *result;
        int len, pid, sd;
        char *buf, host[BUFSIZE], port[BUFSIZE], addr[2*BUFSIZE];

        if(memset(&hints,0, sizeof(struct addrinfo)) < 0){
                perror("memset() ERROR\n");
                exit(-FAILURE);
        }

        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_flags = AI_PASSIVE;

        if(getaddrinfo(argv[1], argv[2], &hints, &result) < 0){
                perror("getaddrinfo() ERROR\n");
                exit(-FAILURE);
        }

        if((sd = socket(result->ai_family, result->ai_socktype, 0)) < 0){
                perror("socket() ERROR\n");
                exit(-FAILURE);
        }

        servlen = result->ai_addrlen;

        if(bind(sd, (struct sockaddr*) result->ai_addr, servlen) < 0){
                perror("bind() ERROR\n");
                exit(-FAILURE);
        }

        while(1){
                buf = malloc(BUFSIZE);

                if((len = recvfrom(sd, buf, BUFSIZE, 0, (struct sockaddr*) &cli, &clilen)) < 0){
                        perror("recvfrom ERROR\n");
                        exit(-FAILURE);
                }

                buf[len] = '\0';

                if(getnameinfo((struct sockaddr*) &cli, clilen, host, BUFSIZE, port, BUFSIZE, NI_NUMERICHOST | NI_NUMERICSERV < 0)){
                        perror("getnameinfo() ERROR\n");
                        exit(-FAILURE);
                }

                sprintf(addr, "Client Address   = %s\nClient Port       = %s\n", host, port);

                if(sendto(sd, addr, strlen(addr), 0, (struct sockaddr*) &cli, clilen) < 0){
                        perror("sendto() ERROR\n");
                        exit(-FAILURE);
                }

                free(buf);
        }

        return SUCCESS;
}
