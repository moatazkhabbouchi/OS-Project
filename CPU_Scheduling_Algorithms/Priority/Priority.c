#include <stdio.h>
#include <stdlib.h>
#include "Priority.h"

liste maximum(liste L, int time){
    liste tmp = L;
    liste max = L;

    if(max->arrival > time) {
        return NULL;
    }
    else{

        while(tmp != NULL){
            if((tmp->priority > max->priority )&& (tmp->arrival <= time) ){
                max = tmp;
                tmp = tmp->next;
            }else{
                tmp = tmp->next;
            }

        }
    }
    return max;
}

struct exec* PR (liste L, int n, int* execT) {

    struct exec* GanttChart = NULL;
    int time = 0;
    liste m = NULL;
    int stop = 0;
    int initialExecution;

    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;


    printf("\033[1;34m \n\tExecution Details: \033[0m\n");

    while (stop < n ) {
        m = maximum(L, time);

        if (m != NULL) {
            struct exec * newEntry = (struct exec*)malloc(sizeof(struct exec));
            newEntry->id = m->pid;
            newEntry->start = time;
            m->execution--;
            time++;
            newEntry->end = time;


            printf("\033[1;32m \ntime %d : \033[0m",time-1);
            printf("\tP%d | Started at %d | Ended at %d | Remaining Time: %d ",
                   m->pid, newEntry->start, time, m->execution);

            GanttChart = addExec2(GanttChart,newEntry->id, newEntry->start, newEntry->end);

            if(m->execution == 0) {
                stop++;
                printf("\033[38;2;249;16;16m => P%d terminated \033[0m\n", m->pid);

                initialExecution = execT[(m->pid)-1];
                int turnaroundTime = newEntry->end - m->arrival;
                int waitingTime = turnaroundTime - initialExecution;

                totalTurnaroundTime += turnaroundTime;
                totalWaitingTime += waitingTime;

                printf("\033[1;34m \tP%d | Turnaround Time: %d | Waiting Time: %d \033[0m \n", m->pid, turnaroundTime, waitingTime);

                L = deleteProcess(L, m);
            }
        }
        else {
            time++;
        }
    }

    float avgTurnaroundTime = (float)totalTurnaroundTime / n;
    float avgWaitingTime = (float)totalWaitingTime / n;

    printf("\n\n \033[1;32m Average Turnaround Time: %.2f \033[0m\n", avgTurnaroundTime);
    printf("\033[1;32m Average Waiting Time: %.2f \033[0m\n\n", avgWaitingTime);


    printf("\n\n");

    return GanttChart;
}
