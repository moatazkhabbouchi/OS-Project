#include <stdio.h>
#include <stdlib.h>
#include "RR.h"

liste ajouterP(liste L ,int time,liste p) {
    if (L == NULL) {
        L = p;
        return L;
    }

    liste tmp1 = L;
    liste tmp2 = NULL;

    while (tmp1 != NULL && tmp1->arrival <= time) {
        tmp2 = tmp1;
        tmp1 = tmp1->next;
    }

    if (tmp2 != NULL) {
        tmp2->next = p;
        p->next = tmp1;
    } else {
        tmp1 = L;
        while (tmp1->next != NULL) {
            tmp1 = tmp1->next;
        }
        tmp1->next = p;
        p->next = NULL;
    }

    return L;
}

int getProcessNumber(liste L) {
    int count = 0;
    liste current = L;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

struct exec* RR (liste L, int quantum, int* execT) {

    struct exec* GanttChart =NULL;
    struct process currentProcess;
    int nbProcess = getProcessNumber(L);
    int i=0;
    int time = 0, stop = 0;
    liste unfinishedList = NULL;
    queue Q = createQueue();

    int initialExecution;

    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;

    printf("\033[1;34m \n\tExecution Details: \033[0m\n");

    while (stop < nbProcess) {

        liste tmp = L;
        while (tmp != NULL) {
            if (tmp->arrival <= time) {
                enqueueProcess(Q,tmp);
                L = deleteProcess(L,tmp);
            }
            tmp = tmp->next;
        }

        tmp = unfinishedList;
        liste tmp2;

        while (tmp != NULL) {
            enqueueProcess(Q,tmp);
            tmp2 = tmp;
            tmp=tmp->next;
            deleteProcess(unfinishedList,tmp2);
        }

        if (isEmpty(Q)) {
            time++;
        }
        else {
            liste remainingProcess;
            while(! isEmpty(Q)) {
                currentProcess = dequeueProcess(Q);

                struct exec* newEntry = (struct exec*)malloc(sizeof(struct exec));
                newEntry->id = currentProcess.pid;
                newEntry->start = time;
                if (currentProcess.execution <= quantum) {
                    time += currentProcess.execution;
                    currentProcess.execution = 0;
                    stop++;

                    initialExecution = execT[(currentProcess.pid)-1];
                    int turnaroundTime = time - currentProcess.arrival;
                    int waitingTime = turnaroundTime - initialExecution;

                    totalTurnaroundTime += turnaroundTime;
                    totalWaitingTime += waitingTime;

                    printf("\tP%d | Started at %d | Ended at %d | Remaining Time: %d ",
                           currentProcess.pid, newEntry->start, time, currentProcess.execution);
                    printf("\033[38;2;249;16;16m => P%d terminated \033[0m\n", currentProcess.pid);

                    printf("\033[1;34m \tP%d | Turnaround Time: %d | Waiting Time: %d \033[0m \n",currentProcess.pid, turnaroundTime, waitingTime);
                }
                else {
                    time+=quantum;
                    currentProcess.execution-=quantum;
                    remainingProcess = createProcess(currentProcess.pid,currentProcess.arrival,currentProcess.execution,currentProcess.priority);
                    ajouterP(L,time,remainingProcess);
                    printf("\tP%d | Started at %d | Ended at %d | Remaining Time: %d\n",
                           currentProcess.pid, newEntry->start, time, currentProcess.execution);

                }

                newEntry->end = time;
                GanttChart = addExec(GanttChart,newEntry);
                i++;

            }
        }

        printf("\033[1;32m\ntime %d :\033[0m", time);

    }

    float avgTurnaroundTime = (float)totalTurnaroundTime / nbProcess;
    float avgWaitingTime = (float)totalWaitingTime / nbProcess;

    printf("\n\n\033[1;32m Average Turnaround Time: %.2f \033[0m\n", avgTurnaroundTime);
    printf("\033[1;32m Average Waiting Time: %.2f \033[0m\n\n", avgWaitingTime);

    return GanttChart;
}
