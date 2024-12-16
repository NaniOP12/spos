#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

void printMatrix(int matrix[MAX_PROCESSES][MAX_RESOURCES], int rows, int cols, const char *name) {
    printf("\n%s Matrix:\n", name);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int detectDeadlock(int processes, int resources, int allocation[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES], int available[MAX_RESOURCES]) {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};
    int work[MAX_RESOURCES];
    int deadlocked[MAX_PROCESSES];
    int deadlockCount = 0;

    // Calculate the Need matrix
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Initialize work array to available resources
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    // Deadlock detection algorithm
    int allProcessesFinished;
    do {
        allProcessesFinished = 1;
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) { // If process is not finished
                int canBeExecuted = 1;

                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {
                        canBeExecuted = 0;
                        break;
                    }
                }

                if (canBeExecuted) {
                    // If process can be executed, update work and mark it finished
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = 1;
                    allProcessesFinished = 0;
                }
            }
        }
    } while (!allProcessesFinished);

    // Check for deadlocked processes
    for (int i = 0; i < processes; i++) {
        if (!finish[i]) {
            deadlocked[deadlockCount++] = i;
        }
    }

    // Output results
    if (deadlockCount > 0) {
        printf("\nDeadlock detected! Deadlocked processes are: ");
        for (int i = 0; i < deadlockCount; i++) {
            printf("P%d ", deadlocked[i]);
        }
        printf("\n");
    } else {
        printf("\nNo deadlock detected. The system is in a safe state.\n");
    }

    return deadlockCount;
}

int main() {
    int processes, resources;
    int allocation[MAX_PROCESSES][MAX_RESOURCES], max[MAX_PROCESSES][MAX_RESOURCES], available[MAX_RESOURCES];

    printf("Enter the number of processes: ");
    scanf("%d", &processes);
    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    // Input Allocation Matrix
    printf("\nEnter the Allocation Matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input Max Matrix
    printf("\nEnter the Max Matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input Available Resources
    printf("\nEnter the Available Resources:\n");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    // Print input matrices
    printMatrix(allocation, processes, resources, "Allocation");
    printMatrix(max, processes, resources, "Max");
    printf("\nAvailable Resources: ");
    for (int i = 0; i < resources; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");

    // Run deadlock detection
    detectDeadlock(processes, resources, allocation, max, available);

    return 0;
}
