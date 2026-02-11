#include <stdio.h>
#define MAX 20

int main() {

    int n;
    int at[MAX], bt[MAX], rt[MAX];
    int ct[MAX], wt[MAX], tat[MAX];
    int time = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i+1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        rt[i] = bt[i];   // copy burst time
    }

    printf("\nGantt Chart:\n");

    // -------- Q0 (Quantum = 8) --------
    for(int i = 0; i < n; i++) {
        if(rt[i] > 0) {
            if(rt[i] > 8) {
                time += 8;
                rt[i] -= 8;
                printf("P%d ", i+1);
            } else {
                time += rt[i];
                printf("P%d ", i+1);
                rt[i] = 0;
                ct[i] = time;
            }
        }
    }

    // -------- Q1 (Quantum = 16) --------
    for(int i = 0; i < n; i++) {
        if(rt[i] > 0) {
            if(rt[i] > 16) {
                time += 16;
                rt[i] -= 16;
                printf("P%d ", i+1);
            } else {
                time += rt[i];
                printf("P%d ", i+1);
                rt[i] = 0;
                ct[i] = time;
            }
        }
    }

    // -------- Q2 (FCFS) --------
    for(int i = 0; i < n; i++) {
        if(rt[i] > 0) {
            time += rt[i];
            printf("P%d ", i+1);
            rt[i] = 0;
            ct[i] = time;
        }
    }

    float avg_wt = 0, avg_tat = 0;

    printf("\n\nProcess\tWT\tTAT\n");

    for(int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        printf("P%d\t%d\t%d\n", i+1, wt[i], tat[i]);

        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat/n);

    return 0;
}

