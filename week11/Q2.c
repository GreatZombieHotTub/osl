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

void look(int req[], int n, int head) {
    int total = 0;
    sort(req, n);

    int i;
    for(i = 0; i < n; i++)
        if(req[i] > head) break;

    // LEFT
    for(int j = i-1; j >= 0; j--) {
        total += abs(req[j] - head);
        head = req[j];
    }

    // RIGHT
    for(int j = i; j < n; j++) {
        total += abs(req[j] - head);
        head = req[j];
    }

    printf("LOOK Total Movement = %d\n", total);
}

void clook(int req[], int n, int head) {
    int total = 0;
    sort(req, n);

    int i;
    for(i = 0; i < n; i++)
        if(req[i] > head) break;

    // RIGHT
    for(int j = i; j < n; j++) {
        total += abs(req[j] - head);
        head = req[j];
    }

    // jump to smallest
    if(i > 0) {
        total += abs(head - req[0]);
        head = req[0];
    }

    // remaining
    for(int j = 1; j < i; j++) {
        total += abs(req[j] - head);
        head = req[j];
    }

    printf("C-LOOK Total Movement = %d\n", total);
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

    printf("\n1.LOOK  2.C-LOOK 3.all\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1: look(req, n, head); break;
        case 2: clook(req, n, head); break;
        case 3: look(req, n, head); 
        clook(req, n, head); break;
        default: printf("Invalid choice\n");
    }

    return 0;
}