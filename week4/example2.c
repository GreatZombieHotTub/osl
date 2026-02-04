#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
if (argc < 2) {
fprintf(stderr, "usage: %s command [args...]\n",
argv[0]);
exit(1);
}
execvp(argv[1], &argv[1]);
// Only runs if execvp() fails
perror("exec failure");
exit(1);
}
