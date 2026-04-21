#include <stdio.h>

#define MAX 10

int main() {
    int blocks[] = {100, 500, 200, 300, 600};
    int procs[]  = {212, 417, 112, 426};
    int nb = 5, np = 4;

    int temp[MAX], alloc[MAX];

    printf("Blocks: ");
    for(int i = 0; i < nb; i++) printf("%d ", blocks[i]);

    printf("\nProcs:  ");
    for(int i = 0; i < np; i++) printf("%d ", procs[i]);

    // ---------- FIRST FIT ----------
    for(int i = 0; i < nb; i++) temp[i] = blocks[i];
    for(int i = 0; i < np; i++) alloc[i] = -1;

    printf("\n\nFirst Fit:\n");

    for(int i = 0; i < np; i++) {
        for(int j = 0; j < nb; j++) {
            if(temp[j] >= procs[i]) {
                alloc[i] = j;
                temp[j] -= procs[i];
                break;
            }
        }

        if(alloc[i] != -1)
            printf("P%d -> B%d\n", i+1, alloc[i]+1);
        else
            printf("P%d -> NA\n", i+1);
    }

    // ---------- BEST FIT ----------
    for(int i = 0; i < nb; i++) temp[i] = blocks[i];
    for(int i = 0; i < np; i++) alloc[i] = -1;

    printf("\nBest Fit:\n");

    for(int i = 0; i < np; i++) {
        int best = -1;

        for(int j = 0; j < nb; j++) {
            if(temp[j] >= procs[i]) {
                if(best == -1 || temp[j] < temp[best])
                    best = j;
            }
        }

        if(best != -1) {
            alloc[i] = best;
            temp[best] -= procs[i];
            printf("P%d -> B%d\n", i+1, best+1);
        } else {
            printf("P%d -> NA\n", i+1);
        }
    }

    // ---------- WORST FIT ----------
    for(int i = 0; i < nb; i++) temp[i] = blocks[i];
    for(int i = 0; i < np; i++) alloc[i] = -1;

    printf("\nWorst Fit:\n");

    for(int i = 0; i < np; i++) {
        int worst = -1;

        for(int j = 0; j < nb; j++) {
            if(temp[j] >= procs[i]) {
                if(worst == -1 || temp[j] > temp[worst])
                    worst = j;
            }
        }

        if(worst != -1) {
            alloc[i] = worst;
            temp[worst] -= procs[i];
            printf("P%d -> B%d\n", i+1, worst+1);
        } else {
            printf("P%d -> NA\n", i+1);
        }
    }

    return 0;
}
