#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


#define SUCCESS 0
#define FAILURE 1
#define BUFSIZE 256


int main(int argc, char ** argv){
        fd_set readfds;
        int fd1, fd2;
        struct timeval tv;
        char *buf;

        remove("tuberia1"); remove("tuberia2");

        if(mkfifo("tuberia1", 0666) < 0 || mkfifo("tuberia2", 0666) < 0){
                perror("mkfifo() ERROR\n");
                exit(-FAILURE);
        }

        fd1 = open("tuberia1", O_RDONLY | O_NONBLOCK);
        fd2 = open("tuberia2", O_RDONLY | O_NONBLOCK);

        while(1){
                FD_ZERO(&readfds);
                FD_SET(fd1, &readfds);
                FD_SET(fd2, &readfds);
                tv.tv_sec = 0;
                tv.tv_usec = 0;
                buf = malloc(BUFSIZE);

                if(select((fd1>fd2 ? fd1 + 1 : fd2 + 1), &readfds, NULL, NULL, &tv) < 0){
                        perror("select() ERROR\n");
                        exit(-FAILURE);
                }

                if(FD_ISSET(fd1, &readfds)){
                        printf("FD1 listo para leer\n");
                        while(read(fd1, buf, BUFSIZE) > 0)
                                printf("Se han leído de la tubería 1 los siguientes datos: \n%s\n", buf);

                        close(fd1);
                        fd1 = open("tuberia1", 0);
                }
                if(FD_ISSET(fd2, &readfds)){
                        printf("FD2 listo para leer\n");
                        while(read(fd2, buf, BUFSIZE) > 0)
                                printf("Se han leído de la tubería 2 los siguientes datos: \n%s\n", buf);

                        close(fd2);
                        fd2 = open("tuberia2", 0);
                }

                free(buf);
        }

        return SUCCESS;
}
