#include <stdio.h>
#include <stdlib.h>

void SCAN(int disk[], int n, int start, int direction, int max) {
    int total_head_movement = 0;
    int current_position = start;
    
    int left[n], right[n];
    int left_count = 0, right_count = 0;

    // Divide requests into left and right of the start position
    for (int i = 0; i < n; i++) {
        if (disk[i] < start) {
            left[left_count++] = disk[i];
        } else {
            right[right_count++] = disk[i];
        }
    }

    // Sort left and right requests
    qsort(left, left_count, sizeof(int), (int (*)(const void*, const void*))strcmp);
    qsort(right, right_count, sizeof(int), (int (*)(const void*, const void*))strcmp);

    // Handle direction
    if (direction == 0) {
        // Moving towards the left
        for (int i = left_count - 1; i >= 0; i--) {
            total_head_movement += abs(current_position - left[i]);
            current_position = left[i];
        }
        total_head_movement += abs(current_position - 0); // Move to 0
        current_position = 0;
        for (int i = 0; i < right_count; i++) {
            total_head_movement += abs(current_position - right[i]);
            current_position = right[i];
        }
    } else {
        // Moving towards the right
        for (int i = 0; i < right_count; i++) {
            total_head_movement += abs(current_position - right[i]);
            current_position = right[i];
        }
        total_head_movement += abs(current_position - max); // Move to max
        current_position = max;
        for (int i = left_count - 1; i >= 0; i--) {
            total_head_movement += abs(current_position - left[i]);
            current_position = left[i];
        }
    }

    printf("\nSCAN Disk Scheduling:\n");
    printf("Total head movement: %d\n", total_head_movement);
}

int main() {
    int n, start, direction, max;

    // Input number of disk requests, starting position, and direction
    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int disk[n];
    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &disk[i]);
    }

    printf("Enter the starting disk position: ");
    scanf("%d", &start);

    printf("Enter the direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    printf("Enter the maximum disk position: ");
    scanf("%d", &max);

    SCAN(disk, n, start, direction, max);

    return 0;
}
