// producer_shm.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
// shm_words.h
#define TEXT_SZ 100

struct shared_data {
    int written;
    char text[TEXT_SZ];
};


int main() {
    int shmid;
    struct shared_data *shared;

    shmid = shmget(1234, sizeof(struct shared_data), 0666 | IPC_CREAT);
    shared = shmat(shmid, NULL, 0);

    printf("Enter a word: ");
    scanf("%s", shared->text);

    shared->written = 1;

    shmdt(shared);
    return 0;
}

