#include <stdio.h>
#include <stdlib.h>

int isPresent(int *frames, int nf, int page) {
    for (int i = 0; i < nf; i++)
        if (frames[i] == page) return 1;
    return 0;
}

// Find LRU victim: page used least recently
int findLRU(int *time, int nf) {
    int min = time[0], pos = 0;
    for (int i = 1; i < nf; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

void lru(int *pages, int np, int nf) {
    int *frames = (int *)malloc(nf * sizeof(int));
    int *time   = (int *)malloc(nf * sizeof(int));
    int faults  = 0, filled = 0;

    for (int i = 0; i < nf; i++) {
        frames[i] = -1;
        time[i]   = 0;
    }

    printf("\n--- LRU Page Replacement ---\n");
    printf("%-10s %-25s %-10s\n", "Page", "Frames", "Fault");

    for (int i = 0; i < np; i++) {
        printf("%-10d ", pages[i]);

        if (!isPresent(frames, nf, pages[i])) {
            int pos;
            if (filled < nf) {
                pos = filled++;
            } else {
                pos = findLRU(time, nf);
            }
            frames[pos] = pages[i];
            time[pos]   = i + 1;
            faults++;

            for (int j = 0; j < nf; j++)
                if (frames[j] != -1) printf("%d ", frames[j]);
            printf("\t\tFault\n");
        } else {
            // Update time for the referenced page
            for (int j = 0; j < nf; j++)
                if (frames[j] == pages[i])
                    time[j] = i + 1;

            for (int j = 0; j < nf; j++)
                if (frames[j] != -1) printf("%d ", frames[j]);
            printf("\t\tNo Fault\n");
        }
    }

    int hits = np - faults;
    printf("\nTotal Page Faults = %d\n", faults);
    printf("Total Page Hits   = %d\n", hits);
    printf("Hit Ratio         = %.2f%%\n", ((float)hits / np) * 100);

    free(frames);
    free(time);
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

    lru(pages, np, nf);

    free(pages);
    return 0;
}