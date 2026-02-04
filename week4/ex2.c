#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        execl("./ex1", "ex1", NULL);

        // Runs only if exec fails
        perror("exec failed");
        exit(1);
    }
    else {
        // Parent process
        wait(NULL);
        printf("Parent: ex1 execution completed\n");
    }

    return 0;
}

