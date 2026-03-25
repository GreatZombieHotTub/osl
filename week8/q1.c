#include <stdio.h>

int main() {
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int allocation[n][m], max[n][m], need[n][m], available[m];

    printf("\nEnter Allocation Matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("\nEnter Max Matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for(int i=0;i<m;i++){
        scanf("%d", &available[i]);
    }

    // Calculate Need
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Safety Algorithm
    int finish[n], safeSeq[n], work[m];

    for(int i=0;i<n;i++) finish[i] = 0;
    for(int i=0;i<m;i++) work[i] = available[i];

    int count = 0;

    while(count < n){
        int found = 0;

        for(int i=0;i<n;i++){
            if(!finish[i]){
                int j;
                for(j=0;j<m;j++){
                    if(need[i][j] > work[j])
                        break;
                }

                if(j == m){
                    for(int k=0;k<m;k++)
                        work[k] += allocation[i][k];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(!found){
            printf("\nSystem is NOT in safe state\n");
            return 0;
        }
    }

    printf("\nSystem is SAFE\nSafe sequence: ");
    for(int i=0;i<n;i++)
        printf("P%d ", safeSeq[i]);

    printf("\n");

    // 🔹 Request Part
    int p;
    printf("\nEnter process number for request: ");
    scanf("%d", &p);

    int request[m];
    printf("Enter request vector:\n");
    for(int i=0;i<m;i++){
        scanf("%d", &request[i]);
    }

    // Check Request <= Need
    for(int i=0;i<m;i++){
        if(request[i] > need[p][i]){
            printf("Error: Exceeds maximum claim\n");
            return 0;
        }
    }

    // Check Request <= Available
    for(int i=0;i<m;i++){
        if(request[i] > available[i]){
            printf("Resources not available, process must wait\n");
            return 0;
        }
    }

    // Pretend allocation
    for(int i=0;i<m;i++){
        available[i] -= request[i];
        allocation[p][i] += request[i];
        need[p][i] -= request[i];
    }

    printf("Request can be granted (system remains safe)\n");

    return 0;
}
