#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


#define SUCCESS 0
#define FAILURE 1


int main(int argc, char ** argv){
        DIR* dir;
        struct dirent *ent;
        struct stat statbuf;

        if(argc < 2){
                perror("argc\n");
                exit(-FAILURE);
        }

        if((dir = opendir(argv[1])) < 0){
                perror("opendir()\n");
                exit(-FAILURE);
        }

        while((ent = readdir(dir)) != NULL){
                printf("-------------------------\n");
                if(stat(ent->d_name, &statbuf) < 0){
                        perror("stat()\n");
                        exit(-FAILURE);
                }

                printf("File name       = %s\n", ent->d_name);
                printf("Owner UID       = %d\n", statbuf.st_uid);
                printf("I-node number   = %ld\n", ent->d_ino);
                printf("Size            = %ld\n", statbuf.st_size);
        }
        printf("-------------------------\n");

        return SUCCESS;
}
