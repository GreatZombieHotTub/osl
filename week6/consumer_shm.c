// consumer_shm.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm_words.h"

int main() {
    int shmid;
    struct shared_data *shared;

    shmid = shmget(1234, sizeof(struct shared_data), 0666 | IPC_CREAT);
    shared = shmat(shmid, NULL, 0);

    while(shared->written != 1);

    printf("Received word: %s\n", shared->text);

    shmdt(shared);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

