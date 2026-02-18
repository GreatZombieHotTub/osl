// consumer_fifo.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO_NAME "myfifo"

int main() {
    int fd;
    int numbers[4];

    fd = open(FIFO_NAME, O_RDONLY);

    read(fd, numbers, sizeof(numbers));

    printf("Received numbers:\n");
    for(int i=0;i<4;i++)
        printf("%d ", numbers[i]);

    printf("\n");

    close(fd);
    unlink(FIFO_NAME);

    return 0;
}

