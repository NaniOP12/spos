#include <stdio.h>

void FCFS(int disk[], int n, int start) {
    int total_head_movement = 0;
    int current_position = start;

    printf("\nFCFS Disk Scheduling:\n");

    for (int i = 0; i < n; i++) {
        total_head_movement += abs(disk[i] - current_position);
        current_position = disk[i];
        printf("Move to %d\n", disk[i]);
    }

    printf("Total head movement: %d\n", total_head_movement);
}

int main() {
    int n, start;

    // Input number of disk requests and starting position
    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int disk[n];
    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &disk[i]);
    }

    printf("Enter the starting disk position: ");
    scanf("%d", &start);

    FCFS(disk, n, start);

    return 0;
}
