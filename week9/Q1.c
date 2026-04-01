#include <stdio.h>
#include <string.h>

#define MAX 10
void firstFit(int blocks[], int nb, int procs[], int np) {
    int alloc[MAX];
    int temp[MAX];
    memset(alloc, -1, sizeof(alloc));
    for (int i = 0; i < nb; i++) temp[i] = blocks[i];

    printf("\n--- First Fit ---\n");
    for (int i = 0; i < np; i++) {
        for (int j = 0; j < nb; j++) {
            if (temp[j] >= procs[i]) {
                alloc[i] = j;
                temp[j] -= procs[i];
                break;
            }
        }
        if (alloc[i] != -1)
            printf("Process %d (%dK) -> Block %d (%dK)\n", i+1, procs[i], alloc[i]+1, blocks[alloc[i]]);
        else
            printf("Process %d (%dK) -> Not Allocated\n", i+1, procs[i]); }}

void bestFit(int blocks[], int nb, int procs[], int np) {
    int alloc[MAX];
    int temp[MAX];
    memset(alloc, -1, sizeof(alloc));
    for (int i = 0; i < nb; i++) temp[i] = blocks[i];
    printf("\n--- Best Fit ---\n");
    for (int i = 0; i < np; i++) {
        int best = -1;
        for (int j = 0; j < nb; j++) {
            if (temp[j] >= procs[i]) {
                if (best == -1 || temp[j] < temp[best])
                    best = j;
            }}
        alloc[i] = best;
        if (best != -1) {
            temp[best] -= procs[i];
            printf("Process %d (%dK) -> Block %d (%dK)\n", i+1, procs[i], best+1, blocks[best]);
        } else {
            printf("Process %d (%dK) -> Not Allocated\n", i+1, procs[i]); }}}

void worstFit(int blocks[], int nb, int procs[], int np) {
    int alloc[MAX];
    int temp[MAX];
    memset(alloc, -1, sizeof(alloc));
    for (int i = 0; i < nb; i++) temp[i] = blocks[i];

    printf("\n--- Worst Fit ---\n");
    for (int i = 0; i < np; i++) {
        int worst = -1;
        for (int j = 0; j < nb; j++) {
            if (temp[j] >= procs[i]) {
                if (worst == -1 || temp[j] > temp[worst])
                    worst = j;
            }}
        alloc[i] = worst;
        if (worst != -1) {
            temp[worst] -= procs[i];
            printf("Process %d (%dK) -> Block %d (%dK)\n", i+1, procs[i], worst+1, blocks[worst]);} 
        else {
            printf("Process %d (%dK) -> Not Allocated\n", i+1, procs[i]);
        }}}

int main() {
    int blocks[] = {100, 500, 200, 300, 600};
    int procs[]  = {212, 417, 112, 426};
    int nb = 5, np = 4;

    printf("Memory Blocks (K): ");
    for (int i = 0; i < nb; i++) printf("%d ", blocks[i]);
    printf("\nProcesses (K):     ");
    for (int i = 0; i < np; i++) printf("%d ", procs[i]);

    firstFit(blocks, nb, procs, np);
    bestFit(blocks, nb, procs, np);
    worstFit(blocks, nb, procs, np);

    printf("\nConclusion: Best-fit makes most efficient use of memory by minimizing leftover holes.\n");
    return 0;
}
