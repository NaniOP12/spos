#include <stdio.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

void calculateRoundRobinWithPriority(Process processes[], int n, int quantum) {
    int current_time = 0, completed = 0;
    int is_completed[n];
    for (int i = 0; i < n; i++) {
        is_completed[i] = 0;
        processes[i].remaining_time = processes[i].burst_time;
    }

    while (completed != n) {
        int highest_priority = -1, selected = -1;

        // Find the highest-priority process that is ready
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !is_completed[i]) {
                if (highest_priority == -1 || processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            current_time++;  // If no process is ready, advance time
        } else {
            // Serve the selected process for the time quantum
            if (processes[selected].remaining_time <= quantum) {
                current_time += processes[selected].remaining_time;
                processes[selected].remaining_time = 0;
                processes[selected].completion_time = current_time;
                processes[selected].turnaround_time = processes[selected].completion_time - processes[selected].arrival_time;
                processes[selected].waiting_time = processes[selected].turnaround_time - processes[selected].burst_time;
                is_completed[selected] = 1;
                completed++;
            } else {
                current_time += quantum;
                processes[selected].remaining_time -= quantum;
            }
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
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter arrival time, burst time, and priority for Process %d: ", i + 1);
        scanf("%d%d%d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    // Calculate Round Robin with Priority times
    calculateRoundRobinWithPriority(processes, n, quantum);

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
