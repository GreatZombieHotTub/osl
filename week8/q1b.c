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
        } }

    printf("\nEnter Max Matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d", &max[i][j]);
        } }

    printf("\nEnter Available Resources:\n");
    for(int i=0;i<m;i++){
        scanf("%d", &available[i]);
    }
    // Calculate Need
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            need[i][j] = max[i][j] - allocation[i][j]; }  }
    while(1) {
        // 🔹 Safety Algorithm
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
                            break; }
                    if(j == m){
                        for(int k=0;k<m;k++)
                            work[k] += allocation[i][k];

                        safeSeq[count++] = i;
                        finish[i] = 1;
                        found = 1;  }} }
            if(!found){
                printf("\nSystem is NOT in safe state\n");
                break;}}
        if(count == n){
            printf("\nSystem is SAFE\nSafe sequence: ");
            for(int i=0;i<n;i++)
                printf("P%d ", safeSeq[i]);
            printf("\n");   }
        // 🔹 Ask for request
        int choice;
        printf("\nDo you want to make a request? (1 = Yes, 0 = Exit): ");
        scanf("%d", &choice);
        if(choice == 0)
            break;
        int p;
        printf("Enter process number: ");
        scanf("%d", &p);
        int request[m];
        printf("Enter request vector:\n");
        for(int i=0;i<m;i++){
            scanf("%d", &request[i]); }
        // Check Request <= Need
        int valid = 1;
        for(int i=0;i<m;i++){
            if(request[i] > need[p][i]){
                printf("Error: Exceeds maximum claim\n");
                valid = 0;
                break; }}
        if(!valid) continue;
        // Check Request <= Available
        for(int i=0;i<m;i++){
            if(request[i] > available[i]){
                printf("Resources not available, process must wait\n");
                valid = 0;
                break;
            }}
        if(!valid) continue;
        // 🔹 Save old state (IMPORTANT)
        int temp_available[m], temp_alloc[n][m], temp_need[n][m];
        for(int i=0;i<m;i++)
            temp_available[i] = available[i];
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                temp_alloc[i][j] = allocation[i][j];
                temp_need[i][j] = need[i][j]; }
        // Pretend allocation
        for(int i=0;i<m;i++){
            available[i] -= request[i];
            allocation[p][i] += request[i];
            need[p][i] -= request[i]; }
        // 🔹 Check safety again
        for(int i=0;i<n;i++) finish[i] = 0;
        for(int i=0;i<m;i++) work[i] = available[i];
        count = 0;
        while(count < n){
            int found = 0;
            for(int i=0;i<n;i++){
                if(!finish[i]){
                    int j;
                    for(j=0;j<m;j++){
                        if(need[i][j] > work[j])
                            break; }
                    if(j == m){
                        for(int k=0;k<m;k++)
                            work[k] += allocation[i][k];
                        finish[i] = 1;
                        found = 1;
                        count++;}}  }
            if(!found) break;
        }
        if(count == n){
            printf("Request GRANTED (System is still safe)\n");
        } else {
            printf("Request DENIED (System would become unsafe)\n");
            // Restore old state
            for(int i=0;i<m;i++)
                available[i] = temp_available[i];
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    allocation[i][j] = temp_alloc[i][j];
                    need[i][j] = temp_need[i][j];  }  }  } }
    printf("\nExiting program...\n");
    return 0;
}
