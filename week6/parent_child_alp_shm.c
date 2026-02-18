// parent_child_shm.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
    int shmid;
    char *shared_mem;

    shmid = shmget(1234, 10, 0666 | IPC_CREAT);
    shared_mem = (char*) shmat(shmid, NULL, 0);

    printf("Enter an alphabet: ");
    scanf(" %c", shared_mem);

    if(fork() == 0) {
        // Child
        *shared_mem = *shared_mem + 1;
        exit(0);
    }
    else {
        wait(NULL);
        printf("Next alphabet from child: %c\n", *shared_mem);
    }

    shmdt(shared_mem);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

