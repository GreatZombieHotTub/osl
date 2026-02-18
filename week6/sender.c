// sender.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msg_st {
    long int msg_type;
    char text[100];
};

int main() {
    int msgid;
    struct msg_st data;

    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

    printf("Enter a number: ");
    scanf("%s", data.text);

    data.msg_type = 1;

    msgsnd(msgid, (void *)&data, sizeof(data.text), 0);

    printf("Number sent to Process B\n");
    return 0;
}

