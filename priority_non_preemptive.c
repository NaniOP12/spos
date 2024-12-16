#include <stdio.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

void calculatePriority(Process processes[], int n) {
    int completed = 0, current_time = 0;
    int is_completed[n];
    for (int i = 0; i < n; i++) is_completed[i] = 0;

    while (completed != n) {
        int highest_priority = -1, selected = -1;

        // Find process with the highest priority
        for (int i = 0; i < n; i++) {
            if (!is_completed[i] && processes[i].arrival_time <= current_time) {
                if (highest_priority == -1 || processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            current_time++;
        } else {
            current_time += processes[selected].burst_time;
            processes[selected].completion_time = current_time;
            processes[selected].turnaround_time = processes[selected].completion_time - processes[selected].arrival_time;
            processes[selected].waiting_time = processes[selected].turnaround_time - processes[selected].burst_time;
            is_completed[selected] = 1;
            completed++;
        }
    }
}

void printTable(Process processes[], int n) {
    printf("\nProcess\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].process_id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].priority,
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
        printf("Enter arrival time, burst time, and priority for Process %d: ", i + 1);
        scanf("%d%d%d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
    }

    // Calculate Priority Scheduling times
    calculatePriority(processes, n);

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
