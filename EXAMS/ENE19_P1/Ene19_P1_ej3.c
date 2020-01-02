#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE 1
#define BUFSIZE 256


int main(int argc, char ** argv){
        struct sockaddr_storage cli;
        socklen_t servlen, clilen;
        struct addrinfo hints, *result;
        int pid, sd, len;
        char *buf, host[BUFSIZE], port[BUFSIZE], datatime[BUFSIZE];
        //char *buf, *host, *port, datatime[BUFSIZE];
        time_t t;
        struct tm *tm;

        if(argc < 3){
                perror("argc\n");
                exit(-FAILURE);
        }

        if(memset(&hints, 0, sizeof(struct addrinfo)) < 0){
                perror("memset()\n");
                exit(-FAILURE);
        }

        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_flags = AI_PASSIVE;

        if(getaddrinfo(argv[1], argv[2], &hints, &result) < 0){
                perror("getaddrinfo()\n");
                exit(-FAILURE);
        }

        servlen = result->ai_addrlen;

        if((sd = socket(result->ai_family, result->ai_socktype, 0)) < 0){
                perror("socket()\n");
                exit(-FAILURE);
        }

        if(bind(sd, (struct sockaddr*) result->ai_addr, servlen) < 0){
                perror("bind()\n");
                exit(-FAILURE);
        }

        while(1){
                buf = malloc(BUFSIZE);

                clilen = sizeof(struct sockaddr*);

                if((len = recvfrom(sd, buf, BUFSIZE, 0, (struct sockaddr*) &cli, &clilen)) < 0){
                        perror("recvfrom()\n");
                        exit(-FAILURE);
                }

                buf[len] = '\0';

                printf("Data received = %s\n", buf);

                if(getnameinfo((struct sockaddr*) &cli, clilen, host, BUFSIZE, port, BUFSIZE, NI_NUMERICHOST) < 0){
                        perror("getnameinfo()\n");
                        exit(-FAILURE);
                }

                printf("Host = %s\n", host);
                printf("Client (Address,Port)   = (%s,%s)\n", host, port);

                t = time(NULL);
                tm = localtime(&t);

                sprintf(datatime, "%d:%d:%d\n", tm->tm_hour, tm->tm_min, tm->tm_sec);

                if(sendto(sd, datatime, strlen(datatime), 0, (struct sockaddr*) &cli, clilen) < 0){
                        perror("sendto()\n");
                        exit(-FAILURE);
                }

                free(buf);
        }

        return SUCCESS;
}
