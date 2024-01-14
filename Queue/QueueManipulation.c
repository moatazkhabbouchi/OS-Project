#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "QueueManipulation.h"

struct exec* addExec(struct exec* E, struct exec* e) {
    if (E == NULL) {
        E = e;
    }
    else {
        struct exec* tmp = E;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = e;

    }
    return E;
}


struct exec* addExec2(struct exec* E, int id, int start, int end) {
    struct exec * e = (struct exec*)malloc(sizeof(struct exec));
    e->id = id;
    e->start = start;
    e->end = end;
    if (E == NULL) {
        E = e;
    }
    else {
        struct exec* tmp = E;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = e;

    }
    return E;
}


queue createQueue() {
    struct queue* queue = (struct queue*)malloc(sizeof(struct queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}


int isEmpty(struct queue* queue) {
    return (queue->front == NULL);
}

void printList(liste L) {
    printf("----------------------------------------------------------------------\n");
    printf("| Process | Arrival Time | Execution Time | Priority |\n");
    printf("----------------------------------------------------------------------\n");

    while (L != NULL) {
        printf("|   P%2d    |     %2d      |      %2d        |    %2d    |\n",
               L->pid, L->arrival, L->execution, L->priority);
        L = L->next;
    }

    printf("----------------------------------------------------------------------\n\n");
}

liste addProcessEnd(liste L, liste p) {
    liste tmp;
    tmp=L;
    if (L == NULL) {
        L = p;
    } else {
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = p;
    }
    return L;
}

liste addProcess(liste L, int id, int arrival_time, int execution_time, int priority) {
    liste newProcess = (liste)malloc(sizeof(struct process));
    newProcess->pid = id;
    newProcess->arrival = arrival_time;
    newProcess->execution = execution_time;
    newProcess->priority = priority;
    newProcess->next = NULL;

    if (L == NULL) {
        L = newProcess;
    } else {
        struct process* temp = L;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newProcess;
    }

    return L;
}


liste createProcess(int id, int arrival, int execution, int priority) {
    liste p = (liste)malloc(sizeof(struct process));
    p->pid=id;
    p->arrival=arrival;
    p->execution=execution;
    p->priority=priority;
    p->next=NULL;
    return p;
}

liste collectProcesses(liste L) {
    FILE* file = fopen("test.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    int id, arrival_time, execution_time, priority;
    while (fscanf(file, "Process %d: Arrival Time %d, Execution Time %d, Priority %d\n", &id, &arrival_time, &execution_time, &priority) == 4) {
        L = addProcess(L, id, arrival_time, execution_time, priority);
    }

    fclose(file);
    return L;
}

liste swap(liste p1, liste p2) {
    liste tmp = p2->next;
    p2->next = p1;
    p1->next = tmp;
    return p2;
}

void bubbleSort(struct process** head, int count) {
    struct process** h;
    int i, j, swapped;

    for (i = 0; i <= count; i++) {

        h = head;
        swapped = 0;

        for (j = 0; j < count - i - 1; j++) {

            liste p1 = *h;
            liste p2 = p1->next;

            if (p1->arrival> p2->arrival) {

                *h = swap(p1, p2);
                swapped = 1;
            }

            h = &(*h)->next;
        }

        if (swapped == 0)
            break;
    }
}

void priorityBubbleSort(struct process** head, int count) {
    struct process** h;
    int i, j, swapped;

    for (i = 0; i <= count; i++) {

        h = head;
        swapped = 0;

        for (j = 0; j < count - i - 1; j++) {

            liste p1 = *h;
            liste p2 = p1->next;

            if (p1->priority> p2->priority) {

                *h = swap(p1, p2);
                swapped = 1;
            }

            h = &(*h)->next;
        }

        if (swapped == 0)
            break;
    }
}

void enqueueProcess(queue queue, struct process* process) {

    if (isEmpty(queue)) {
        queue->front = process;
        queue->rear = process;
    } else {
        queue->rear->next = process;
        queue->rear = process;
    }
}

struct process dequeueProcess(queue queue) {
    if (isEmpty(queue)) {
        printf("Process Queue is empty, cannot dequeue.\n");
    }
    liste removedProcess = queue->front;
    struct process process = *removedProcess;
    queue->front = queue->front->next;
    free(removedProcess);
    return process;
}


void displayQueue(struct queue* queue) {
    if (isEmpty(queue)) {
        printf("Process Queue is empty.\n");
    }
    printf("Processes in the Queue:\n");
    struct process* tmp = queue->front;
    while (tmp != NULL) {
        printf("ID: %d, Arrival Time: %d, Execution Time: %d, Priority: %d\n",
               tmp->pid, tmp->arrival, tmp->execution, tmp->priority);
        tmp = tmp->next;
    }
}

int sumExecution(liste L) {
    int s=0;
    liste tmp = L;
    while (tmp != NULL) {
        s+=tmp->execution;
        tmp=tmp->next;
    }
    return s;
}

liste deleteProcess(liste L, liste p) {
    liste tmp = L;

    if (tmp->pid == p->pid) {
        L= tmp->next;
        tmp->next = NULL;
    }
    else {
        while ((tmp->next)->pid != p->pid) {
            tmp=tmp->next;
        }

        tmp->next = (tmp->next)->next;
    }
    return L;
}

liste PrioritySort(liste L) {
    struct process* current;
    struct process* nextProcess;
    int swapped;

    if (L == NULL)
        return L;

    do {
        swapped = 0;
        current = L;

        while (current->next != NULL) {
            nextProcess = current->next;

            if (current->priority < nextProcess->priority) {

                int tmpId = current->pid;
                int tmpArrival = current->arrival;
                int tmpExecution = current->execution;
                int tmpPriority = current->priority;

                current->pid = nextProcess->pid;
                current->arrival = nextProcess->arrival;
                current->execution = nextProcess->execution;
                current->priority = nextProcess->priority;

                nextProcess->pid = tmpId;
                nextProcess->arrival = tmpArrival;
                nextProcess->execution = tmpExecution;
                nextProcess->priority = tmpPriority;

                swapped = 1;
            }

            current = current->next;
        }
    } while (swapped);

    return L;
}


int* getExecutionTimes (liste L, int n) {

    int* initialExecutionTimes = (int*)malloc(n * sizeof(int));

    int i = 0;
    while (L != NULL && i < n) {
        initialExecutionTimes[i] = L->execution;
        L = L->next;
        i++;
    }
    return initialExecutionTimes;
}

