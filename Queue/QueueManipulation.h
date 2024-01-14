#ifndef SE_PROJECT_PROCESS_SCHEDULING_QUEUE_MANIPULATION_H
#define SE_PROJECT_PROCESS_SCHEDULING_QUEUE_MANIPULATION_H

#include <stdbool.h>

struct process {
    int pid, arrival, execution, priority;
    struct process* next;
};

typedef struct process* liste;

struct queue {
    struct process* front;
    struct process* rear;
};

typedef struct queue* queue;

struct exec {
    int id, start, end;
    struct exec* next;
};

struct exec* addExec(struct exec* E, struct exec* e);

queue createQueue();

int isEmpty(struct queue* queue);

void printList(liste L);

liste addProcessEnd(liste L, liste p);

liste addProcess(liste L, int id, int arrival_time, int execution_time, int priority);


liste createProcess(int id, int arrival, int execution, int priority);

liste collectProcesses(liste L);

liste swap(liste p1, liste p2);

void bubbleSort(struct process** head, int count);

void priorityBubbleSort(struct process** head, int count) ;

void enqueueProcess(queue queue, struct process* process);

struct process dequeueProcess(queue queue);

void displayQueue(struct queue* queue);

int sumExecution(liste L);

liste deleteProcess(liste L, liste p);

struct exec* addExec2(struct exec* E, int id, int start, int end);

int* getExecutionTimes (liste L, int n);

liste PrioritySort(liste L);

#endif
