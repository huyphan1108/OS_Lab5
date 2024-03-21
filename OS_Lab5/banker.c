#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_PROCESSES 5
#define NUMBER_OF_RESOURCES 4


int main() {
    int available[NUMBER_OF_RESOURCES]; // the available amount of each resource
    int claim[NUMBER_OF_PROCESSES][NUMBER_OF_RESOURCES]; // the claim of each process
    int allocation[NUMBER_OF_PROCESSES][NUMBER_OF_RESOURCES]; //allocation per process
    int need[NUMBER_OF_PROCESSES][NUMBER_OF_RESOURCES]; //C – A
    int f[NUMBER_OF_PROCESSES], ans[NUMBER_OF_PROCESSES], ind = 0;

    FILE* file = fopen("inp3.txt", "r");
    char c;

    //read from input file and store available, allocation, and claim
    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            fscanf(file, "%d", &claim[i][j]);
        }
    }
    //skip the next line
    fscanf(file, "%c", &c);

    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            fscanf(file, "%d", &allocation[i][j]);
        }
    }
    //skip a line
    fscanf(file, "%c", &c);

    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        fscanf(file, "%d", &available[i]);
    }
    fclose(file);
    
    //get need matrix
    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++)
            need[i][j] = claim[i][j] - allocation[i][j];
    }
    
    //print claim, allocation, and need matrix to the screen
    printf("Claim\t\t\tAllocation\t\t\tC - A\n");
    printf("\tA B C D\t\t\tA B C D\t\t\tA B C D\n");
    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            printf("%d ", claim[i][j]);
        }
        printf("\t");
        printf("P%d\t", i);
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\t");
        printf("P%d\t", i);
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    
    
    printf("\nAvailable \nA B C D\n");
    for(int i = 0; i < NUMBER_OF_RESOURCES; i++){
        printf("%d ", available[i]);
    }
    printf("\n\n");
    
    for (int i = 0; i < NUMBER_OF_PROCESSES; i++){
        f[i] = 0;
    }
    
    //Initial Available
    printf("Available\t");
    for(int i = 0; i < NUMBER_OF_RESOURCES; i++){
        printf("%d ", available[i]);
    }
    printf("\n");
    
    int y = 0;
    //looping back to check
    for (int k = 0; k < NUMBER_OF_PROCESSES; k++) {
        for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
            if (f[i] == 0) {
 
                int flag = 0;
                //check if there is any process can run
                for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
                    if (need[i][j] > available[j]){
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    ans[ind++] = i;
                    printf("P%d runs\t\t",i);
                    for (y = 0; y < NUMBER_OF_RESOURCES; y++){
                        printf("%d ", allocation[i][y]);
                        available[y] += allocation[i][y];
                    }
                    printf("\n");
                    //print new Available matrix
                    printf("Available\t");
                        for(int i = 0; i < NUMBER_OF_RESOURCES; i++){
                            printf("%d ", available[i]);
                        }
                    printf("\n");
                    f[i] = 1;
                    
                }
            }
        }
    }
    
    int flag = 1;
    //check for deadlock
    for (int i = 0; i < NUMBER_OF_PROCESSES; i++){
        if (f[i] == 0){
            flag = 0;
            printf("No other process can run\n\n");
            break;
        }
    }
    //print process that cannot run
    if (flag == 0)
    {
        printf("Deadlock. Process cannot run: ");
        for (int i = 0; i < NUMBER_OF_PROCESSES; i++){
            if (f[i] == 0){
                printf("P%d, ", i);
            }
        }
    }
    
    
    if (flag == 1)
    {
        printf("\nYes, the initial state is a safe state. Safe sequence: ");
        for (int i = 0; i < NUMBER_OF_PROCESSES; i++)
        {
            printf("P%d, ", ans[i]);
        }
    }
    return 0;
}
