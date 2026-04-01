#include <stdio.h>
#include <stdlib.h>

// Check if page is already in frames
int isPresent(int *frames, int nf, int page) {
    for (int i = 0; i < nf; i++)
        if (frames[i] == page) return 1;
    return 0;
}

// FIFO Page Replacement
void fifo(int *pages, int np, int nf) {
    int *frames = (int *)malloc(nf * sizeof(int));
    int faults = 0, pointer = 0;

    for (int i = 0; i < nf; i++) frames[i] = -1;

    printf("\n--- FIFO Page Replacement ---\n");
    printf("%-10s %-20s %-10s\n", "Page", "Frames", "Fault");

    for (int i = 0; i < np; i++) {
        printf("%-10d ", pages[i]);

        if (!isPresent(frames, nf, pages[i])) {
            frames[pointer] = pages[i];
            pointer = (pointer + 1) % nf;
            faults++;

            for (int j = 0; j < nf; j++)
                if (frames[j] != -1) printf("%d ", frames[j]);
            printf("\t\tFault\n");
        } else {
            for (int j = 0; j < nf; j++)
                if (frames[j] != -1) printf("%d ", frames[j]);
            printf("\t\tNo Fault\n");
        }
    }

    printf("\nTotal Page Faults (FIFO) = %d\n", faults);
    printf("Hit Ratio = %.2f%%\n", ((float)(np - faults) / np) * 100);
    free(frames);
}

// Find optimal victim: page used farthest in future
int findOptimal(int *frames, int nf, int *pages, int np, int current) {
    int farthest = -1, victim = 0;

    for (int i = 0; i < nf; i++) {
        int j;
        for (j = current + 1; j < np; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    victim = i;
                }
                break;
            }
        }
        // Page not used in future at all — best to replace
        if (j == np) return i;
    }
    return victim;
}

// Optimal Page Replacement
void optimal(int *pages, int np, int nf) {
    int *frames = (int *)malloc(nf * sizeof(int));
    int faults = 0, filled = 0;

    for (int i = 0; i < nf; i++) frames[i] = -1;

    printf("\n--- Optimal Page Replacement ---\n");
    printf("%-10s %-20s %-10s\n", "Page", "Frames", "Fault");

    for (int i = 0; i < np; i++) {
        printf("%-10d ", pages[i]);

        if (!isPresent(frames, nf, pages[i])) {
            if (filled < nf) {
                frames[filled++] = pages[i];
            } else {
                int victim = findOptimal(frames, nf, pages, np, i);
                frames[victim] = pages[i];
            }
            faults++;

            for (int j = 0; j < nf; j++)
                if (frames[j] != -1) printf("%d ", frames[j]);
            printf("\t\tFault\n");
        } else {
            for (int j = 0; j < nf; j++)
                if (frames[j] != -1) printf("%d ", frames[j]);
            printf("\t\tNo Fault\n");
        }
    }

    printf("\nTotal Page Faults (Optimal) = %d\n", faults);
    printf("Hit Ratio = %.2f%%\n", ((float)(np - faults) / np) * 100);
    free(frames);
}

int main() {
    int np, nf;

    printf("Enter number of frames: ");
    scanf("%d", &nf);

    printf("Enter number of pages: ");
    scanf("%d", &np);

    int *pages = (int *)malloc(np * sizeof(int));

    printf("Enter page reference string:\n");
    for (int i = 0; i < np; i++)
        scanf("%d", &pages[i]);

    fifo(pages, np, nf);
    optimal(pages, np, nf);

    free(pages);
    return 0;
}