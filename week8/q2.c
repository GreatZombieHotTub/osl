#include <stdio.h>

int main() {
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int allocation[n][m], request[n][m], available[m];

    printf("\nEnter Allocation Matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("\nEnter Request Matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d", &request[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for(int i=0;i<m;i++){
        scanf("%d", &available[i]);
    }

    int finish[n], work[m];

    // Initialize finish
    for(int i=0;i<n;i++){
        int zero = 1;
        for(int j=0;j<m;j++){
            if(allocation[i][j] != 0){
                zero = 0;
                break;
            }
        }
        finish[i] = zero;
    }

    for(int i=0;i<m;i++)
        work[i] = available[i];

    int changed = 1;

    while(changed){
        changed = 0;

        for(int i=0;i<n;i++){
            if(!finish[i]){
                int j;
                for(j=0;j<m;j++){
                    if(request[i][j] > work[j])
                        break;
                }

                if(j == m){
                    for(int k=0;k<m;k++)
                        work[k] += allocation[i][k];

                    finish[i] = 1;
                    changed = 1;
                }
            }
        }
    }

    int deadlock = 0;

    printf("\n");

    for(int i=0;i<n;i++){
        if(!finish[i]){
            printf("P%d is deadlocked\n", i);
            deadlock = 1;
        }
    }

    if(!deadlock)
        printf("No deadlock detected\n");

    return 0;
}
