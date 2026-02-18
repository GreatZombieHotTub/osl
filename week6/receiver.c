// receiver.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msg_st {
    long int msg_type;
    char text[100];
};

int isPalindrome(char num[]) {
    int i, len = strlen(num);
    for(i = 0; i < len/2; i++) {
        if(num[i] != num[len - i - 1])
            return 0;
    }
    return 1;
}

int main() {
    int msgid;
    struct msg_st data;

    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

    msgrcv(msgid, (void *)&data, sizeof(data.text), 0, 0);

    printf("Received number: %s\n", data.text);

    if(isPalindrome(data.text))
        printf("It is Palindrome\n");
    else
        printf("Not a Palindrome\n");

    msgctl(msgid, IPC_RMID, 0);

    return 0;
}

