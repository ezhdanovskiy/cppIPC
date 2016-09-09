#include "Logger.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <err.h>
#include <stdlib.h>

#define SHMSIZE 27
#define SHMKEY 2009

int main() {
    srand(time(0));
    int shmid;
    char *shm;

    if(fork() == 0) {
        shmid = shmget(SHMKEY, SHMSIZE, 0);
        LOG1(shmid);
        if(shmid == -1){
            err(1, "shmget");
        }
        shm = (char*)shmat(shmid, 0, 0);
        char *s = (char *) shm;
        *s = '\0';  /* Set first location to string terminator, for later append */
        int i;
        for(i=0; i<5; i++) {
            int n = rand() % 100 ;
            sprintf(s, "%s%d", s, n);  /* Append number to string */
        }
        LOG1(shm);
        shmdt(shm);
    }
    else {
        /* Variable s removed, it wasn't used */
        /* Removed first call to wait as it held up parent process */
//        usleep(1000);
        shmid = shmget(SHMKEY, SHMSIZE, 0666 | IPC_CREAT);
        LOG1(shmid);
        if(shmid == -1){
            err(1, "shmget");
        }
        shm = (char*)shmat(shmid, 0, 0);
        wait(NULL);
        LOG1(shm);
        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}