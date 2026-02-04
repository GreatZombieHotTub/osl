#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) {   // Child
        printf("Child Process\n");
        printf("PID  = %d\n", getpid());
        printf("PPID = %d\n", getppid());
        exit(0);
    }
    else {                // Parent
        wait(NULL);
        printf("Parent Process\n");
        printf("PID  = %d\n", getpid());
        printf("PPID = %d\n", getppid());
    }
    return 0;
}

