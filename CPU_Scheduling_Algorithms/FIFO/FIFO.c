#include <stdio.h>
#include <stdlib.h>
#include "FIFO.h"

struct exec* FIFO(liste L) {
    struct exec* GanttChart = NULL;
    struct exec* tail = NULL;

    int count = 0;
    struct process* temp = L;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    bubbleSort(&L, count);

    printf("\033[1;34m \tExecution Details: \033[0m\n");

    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;

    int currentTime = L->arrival;

    while (L != NULL) {
        struct exec* newEntry = (struct exec*)malloc(sizeof(struct exec));
        newEntry->id = L->pid;
        newEntry->start = currentTime;
        newEntry->end = currentTime + L->execution;
        newEntry->next = NULL;

        if (GanttChart == NULL) {
            GanttChart = newEntry;
            tail = newEntry;
        } else {
            tail->next = newEntry;
            tail = newEntry;
        }

        int turnaroundTime = newEntry->end - L->arrival;
        int waitingTime = turnaroundTime - L->execution;

        totalTurnaroundTime += turnaroundTime;
        totalWaitingTime += waitingTime;

        printf("\tP%d | Started at %d | Ended at %d | Turnaround Time: %d | Waiting Time: %d\n",
               L->pid, newEntry->start, newEntry->end, turnaroundTime, waitingTime);

        currentTime += L->execution;
        L = L->next;
    }

    float avgTurnaroundTime = (float)totalTurnaroundTime / count;
    float avgWaitingTime = (float)totalWaitingTime / count;

    printf("\n\033[1;32m Average Turnaround Time: %.2f \033[0m\n", avgTurnaroundTime);
    printf("\033[1;32m Average Waiting Time: %.2f \033[0m\n\n", avgWaitingTime);

    printf("\n");

    return GanttChart;
}
