// producer_fifo.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME "myfifo"

int main() {
    int fd;
    int numbers[4];

    mkfifo(FIFO_NAME, 0666);

    fd = open(FIFO_NAME, O_WRONLY);

    printf("Enter 4 integers:\n");
    for(int i=0;i<4;i++)
        scanf("%d",&numbers[i]);

    write(fd, numbers, sizeof(numbers));

    close(fd);
    return 0;
}

