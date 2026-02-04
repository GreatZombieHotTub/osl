#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {   // Child
        printf("Child exiting\n");
        exit(0);
    }
    else {            // Parent
        sleep(20);    // Parent sleeps, no wait()
        printf("Parent exiting\n");
    }
    return 0;
}

