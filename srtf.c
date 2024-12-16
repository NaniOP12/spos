#include <stdio.h>
#include <limits.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

void calculateSRTF(Process processes[], int n) {
    int current_time = 0, completed = 0;
    int min_remaining = INT_MAX, shortest = -1;
    int is_completed[n];
    for (int i = 0; i < n; i++) {
        is_completed[i] = 0;
        processes[i].remaining_time = processes[i].burst_time;
    }

    while (completed != n) {
        // Find process with shortest remaining time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !is_completed[i]) {
                if (processes[i].remaining_time < min_remaining) {
                    min_remaining = processes[i].remaining_time;
                    shortest = i;
                }
            }
        }

        if (shortest == -1) {
            current_time++;
        } else {
            // Process the shortest job
            processes[shortest].remaining_time--;
            current_time++;
            if (processes[shortest].remaining_time == 0) {
                processes[shortest].completion_time = current_time;
                processes[shortest].turnaround_time = processes[shortest].completion_time - processes[shortest].arrival_time;
                processes[shortest].waiting_time = processes[shortest].turnaround_time - processes[shortest].burst_time;
                is_completed[shortest] = 1;
                completed++;
                shortest = -1;
                min_remaining = INT_MAX;
            }
        }
    }
}

void printTable(Process processes[], int n) {
    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               processes[i].process_id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter arrival time and burst time for Process %d: ", i + 1);
        scanf("%d%d", &processes[i].arrival_time, &processes[i].burst_time);
    }

    // Calculate SRTF times
    calculateSRTF(processes, n);

    // Print the result
    printTable(processes, n);

    // Calculate average Turnaround Time and Waiting Time
    float total_turnaround_time = 0, total_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        total_turnaround_time += processes[i].turnaround_time;
        total_waiting_time += processes[i].waiting_time;
    }

    printf("\nAverage Turnaround Time: %.2f", total_turnaround_time / n);
    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);

    return 0;
}
