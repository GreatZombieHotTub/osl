#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    for(int i = 0; i < n-1; i++)
        for(int j = 0; j < n-i-1; j++)
            if(arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
}

void fcfs(int req[], int n, int head) {
    int total = 0;
    for(int i = 0; i < n; i++) {
        total += abs(req[i] - head);
        head = req[i];
    }
    printf("FCFS Total Movement = %d\n", total);
}

void sstf(int req[], int n, int head) {
    int visited[100] = {0}, total = 0;

    for(int i = 0; i < n; i++) {
        int min = 9999, index = -1;
        for(int j = 0; j < n; j++) {
            if(!visited[j] && abs(req[j] - head) < min) {
                min = abs(req[j] - head);
                index = j;
            }
        }
        total += min;
        head = req[index];
        visited[index] = 1;
    }
    printf("SSTF Total Movement = %d\n", total);
}

void scan(int req[], int n, int head) {
    int total = 0;
    sort(req, n);

    int i;
    for(i = 0; i < n; i++)
        if(req[i] > head) break;

    // LEFT first (as per your question)
    for(int j = i-1; j >= 0; j--) {
        total += abs(req[j] - head);
        head = req[j];
    }

    total += head; // go to 0
    head = 0;

    for(int j = i; j < n; j++) {
        total += abs(req[j] - head);
        head = req[j];
    }

    printf("SCAN Total Movement = %d\n", total);
}

void cscan(int req[], int n, int head) {
    int total = 0, disk_size = 200;
    sort(req, n);

    int i;
    for(i = 0; i < n; i++)
        if(req[i] > head) break;

    // RIGHT side
    for(int j = i; j < n; j++) {
        total += abs(req[j] - head);
        head = req[j];
    }

    // go to end
    total += abs((disk_size - 1) - head);
    head = 0;

    // LEFT side
    for(int j = 0; j < i; j++) {
        total += abs(req[j] - head);
        head = req[j];
    }

    printf("C-SCAN Total Movement = %d\n", total);
}

int main() {
    int n, head, choice;
    int req[100];

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter requests: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter head position: ");
    scanf("%d", &head);

    printf("\n1.FCFS  2.SSTF  3.SCAN  4.C-SCAN 5.all\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1: fcfs(req, n, head); break;
        case 2: sstf(req, n, head); break;
        case 3: scan(req, n, head); break;
        case 4: cscan(req, n, head); break;
        case 5: fcfs(req, n, head); 
        sstf(req, n, head); 
        scan(req, n, head);
        cscan(req, n, head); break;
        default: printf("Invalid choice\n");
    }

    return 0;
}