#include <stdio.h>

#define MAX 20

void fcfs(int n, int at[], int bt[]);
void srtf(int n, int at[], int bt[]);
void roundRobin(int n, int at[], int bt[], int quantum);
void priorityNP(int n, int at[], int bt[], int pr[]);

void fcfs(int n, int at[], int bt[]) {
    int ct[MAX], wt[MAX], tat[MAX];
    int time = 0;

    printf("\nGantt Chart:\n");

    for(int i = 0; i < n; i++) {

        if(time < at[i])
            time = at[i];

        time += bt[i];
        ct[i] = time;

        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        printf("P%d ", i+1);
    }

    float avg_wt = 0, avg_tat = 0;

    printf("\n\nProcess\tWT\tTAT\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\n", i+1, wt[i], tat[i]);
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("Average WT = %.2f\n", avg_wt/n);
    printf("Average TAT = %.2f\n", avg_tat/n);
}

void srtf(int n, int at[], int bt[]) {
    int rt[MAX], ct[MAX], wt[MAX], tat[MAX];
    int completed = 0, time = 0, min, shortest;

    for(int i = 0; i < n; i++)
        rt[i] = bt[i];

    printf("\nGantt Chart:\n");

    while(completed != n) {

        min = 9999;
        shortest = -1;

        for(int i = 0; i < n; i++) {
            if(at[i] <= time && rt[i] > 0 && rt[i] < min) {
                min = rt[i];
                shortest = i;
            }
        }

        if(shortest == -1) {
            time++;
            continue;
        }

        rt[shortest]--;
        printf("P%d ", shortest+1);
        time++;

        if(rt[shortest] == 0) {
            completed++;
            ct[shortest] = time;
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

    printf("Average WT = %.2f\n", avg_wt/n);
    printf("Average TAT = %.2f\n", avg_tat/n);
}

void roundRobin(int n, int at[], int bt[], int quantum) {
    int rt[MAX], wt[MAX], tat[MAX], ct[MAX];
    int time = 0, completed = 0;

    for(int i = 0; i < n; i++)
        rt[i] = bt[i];

    printf("\nGantt Chart:\n");

    while(completed != n) {

        for(int i = 0; i < n; i++) {

            if(rt[i] > 0 && at[i] <= time) {

                if(rt[i] > quantum) {
                    time += quantum;
                    rt[i] -= quantum;
                    printf("P%d ", i+1);
                }
                else {
                    time += rt[i];
                    printf("P%d ", i+1);
                    rt[i] = 0;
                    ct[i] = time;
                    completed++;
                }
            }
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

    printf("Average WT = %.2f\n", avg_wt/n);
    printf("Average TAT = %.2f\n", avg_tat/n);
}
void priorityNP(int n, int at[], int bt[], int pr[]) {
    int completed = 0, time = 0;
    int visited[MAX] = {0};
    int ct[MAX], wt[MAX], tat[MAX];

    printf("\nGantt Chart:\n");

    while(completed != n) {

        int idx = -1;
        int highest = -1;

        for(int i = 0; i < n; i++) {
            if(at[i] <= time && visited[i] == 0) {
                if(pr[i] > highest) {
                    highest = pr[i];
                    idx = i;
                }
            }
        }

        if(idx == -1) {
            time++;
            continue;
        }

        time += bt[idx];
        ct[idx] = time;
        visited[idx] = 1;
        completed++;

        printf("P%d ", idx+1);
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

    printf("Average WT = %.2f\n", avg_wt/n);
    printf("Average TAT = %.2f\n", avg_tat/n);
}
int main() {
    int n, choice;
    int at[MAX], bt[MAX], pr[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("Process %d\n", i+1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Priority: ");
        scanf("%d", &pr[i]);
    }

    do {
        printf("\n1.FCFS\n2.SRTF\n3.Round Robin\n4.Priority (Non-preemptive)\n5.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: fcfs(n, at, bt); break;
            case 2: srtf(n, at, bt); break;
            case 3: roundRobin(n, at, bt, 10); break;
            case 4: priorityNP(n, at, bt, pr); break;
        }
    } while(choice != 5);

    return 0;
}

