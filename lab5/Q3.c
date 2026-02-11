#include <stdio.h>
#define MAX 20

int main() {

    int n;
    int at[MAX], bt[MAX], deadline[MAX];
    int rt[MAX], ct[MAX], wt[MAX], tat[MAX];

    int time = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i+1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Deadline: ");
        scanf("%d", &deadline[i]);

        rt[i] = bt[i];
    }

    printf("\nGantt Chart:\n");

    while(completed != n) {

        int idx = -1;
        int earliest = 9999;

        for(int i = 0; i < n; i++) {
            if(at[i] <= time && rt[i] > 0) {
                if(deadline[i] < earliest) {
                    earliest = deadline[i];
                    idx = i;
                }
            }
        }

        if(idx == -1) {
            time++;
            continue;
        }

        rt[idx]--;
        printf("P%d ", idx+1);
        time++;

        if(rt[idx] == 0) {
            ct[idx] = time;
            completed++;
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

