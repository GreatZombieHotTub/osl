#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

int n;
int arr[100];

void* bubble_sort(void* arg) {
    clock_t start = clock();
    int temp[100];
    for (int i = 0; i < n; i++) temp[i] = arr[i];

    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (temp[j] > temp[j+1]) {
                int t = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = t;
            }

    clock_t end = clock();
    printf("Bubble Sort Time: %f\n", (double)(end-start)/CLOCKS_PER_SEC);
    pthread_exit(NULL);
}

void* selection_sort(void* arg) {
    clock_t start = clock();
    int temp[100];
    for (int i = 0; i < n; i++) temp[i] = arr[i];

    for (int i = 0; i < n-1; i++) {
        int min = i;
        for (int j = i+1; j < n; j++)
            if (temp[j] < temp[min]) min = j;
        int t = temp[i];
        temp[i] = temp[min];
        temp[min] = t;
    }

    clock_t end = clock();
    printf("Selection Sort Time: %f\n", (double)(end-start)/CLOCKS_PER_SEC);
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    pthread_create(&t1, NULL, bubble_sort, NULL);
    pthread_create(&t2, NULL, selection_sort, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Final sorted array (bubble sort)
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1]) {
                int t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
            }

    printf("Final Sorted Array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}

