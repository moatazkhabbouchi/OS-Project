#include <stdio.h>
#include <stdlib.h>
#include "MultiLevel.h"


int priorityOcc(liste L)
{
    int occ=1;
    PrioritySort(L);
    liste tmp=L;
    while (tmp->next != NULL)
    {
        if (tmp->priority != (tmp->next)->priority)
        {
            occ++;
        }
        tmp=tmp->next;
    }
    return occ;
}


liste ajouterP1(liste L,int time,liste p)
{
    if (L == NULL)
    {
        L = p;
        return L;
    }

    liste tmp1 = L;
    liste tmp2 = NULL;

    while (tmp1 != NULL && tmp1->arrival <= time)
    {
        tmp2 = tmp1;
        tmp1 = tmp1->next;
    }

    if (tmp2 != NULL)
    {
        tmp2->next = p;
        p->next = tmp1;
    }
    else
    {
        tmp1 = L;
        while (tmp1->next != NULL)
        {
            tmp1 = tmp1->next;
        }
        tmp1->next = p;
        p->next = NULL;
    }

    return L;
}


liste* fillTable(liste L, int priorityOcc) {
    liste* t = malloc(priorityOcc * sizeof(liste));
    int pr;

    liste tmp = L;
    for (int i = 0; i < priorityOcc; ++i)
    {
        if (tmp == NULL)
        {
            t[i] = NULL;
            continue;
        }

        pr = tmp->priority;
        liste p = NULL, process;

        while (tmp != NULL && tmp->priority == pr)
        {
            process = createProcess(tmp->pid, tmp->arrival, tmp->execution, tmp->priority);
            p = addProcessEnd(p, process);
            tmp = tmp->next;
        }

        t[i] = p;
        if (tmp != NULL)
        {
            pr = tmp->priority;
        }
    }

    return t;
}


void deleteFirstNodeAtIndex(liste* t, int index) {
    if (t[index] == NULL) {
        return;
    }

    liste firstNode = t[index];

    t[index] = t[index]->next;

    free(firstNode);
    firstNode = NULL;
}



struct exec* MultiLevel(liste L, int n, int quantum, int* execT) {

    struct exec* E = NULL;
    int time = 0;
    int stop = 0;
    liste process;
    int nbPriority = priorityOcc(L);
    PrioritySort(L);
    printList(L);
    liste* tab;
    tab = fillTable(L, nbPriority);
    printf("Nb priority : %d\n", nbPriority);
    int i=0;
    int s=0,level=0;

    int initialExecution;

    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;

    while(stop<n) {
        while(i<nbPriority) {
            if(tab[i]==NULL){
                i++;
            }
            else {
                if (tab[i]->arrival <= time){
                    level=i;

                    if (tab[i]->execution != 0) {

                        if(tab[i]->next!=NULL) {
                            printf("The List contain more than an element\n");

                            if((tab[i]->next)->arrival<=time) {

                                if(level!=i){
                                    s=0;
                                }
                                if(s< quantum){
                                    printf("exection < quantum : s = %d\n",s);

                                    struct exec * e = (struct exec*)malloc(sizeof(struct exec));
                                    e->id = tab[i]->pid;
                                    e->start = time;
                                    tab[i]->execution--;
                                    time++;
                                    e->end = time;
                                    E = addExec2(E,e->id, e->start, e->end);
                                    s++;
                                    printList(tab[i]);

                                    i=0;
                                }
                                else {
                                    s=0;
                                    process = createProcess(tab[i]->pid,tab[i]->arrival,tab[i]->execution,tab[i]->priority);
                                    deleteFirstNodeAtIndex(tab, i);
                                    tab[i]=ajouterP1(tab[i],time,process);
                                    printList(tab[i]);
                                    i=0;
                                }
                            } else {
                                struct exec * e = (struct exec*)malloc(sizeof(struct exec));
                                e->id = tab[i]->pid;
                                e->start = time;
                                tab[i]->execution--;
                                time++;
                                e->end = time;
                                E = addExec2(E,e->id, e->start, e->end);
                                free(e);
                                s++;
                                printList(tab[i]);
                                i=0;
                            }
                        }
                        else {
                            printf("The list contain just an element\n");
                            struct exec * e = (struct exec*)malloc(sizeof(struct exec));
                            e->id = tab[i]->pid;
                            e->start = time;
                            tab[i]->execution--;
                            time++;
                            e->end = time;
                            E = addExec2(E,e->id, e->start, e->end);
                            printList(tab[i]);
                            i=0;
                        }

                    }
                    else{
                        printf("\033[1;32m \ntime %d : \033[0m",time);
                        printf("\033[38;2;249;16;16m => P%d terminated \033[0m\n", tab[i]->pid);

                        initialExecution = execT[(tab[i]->pid)-1];
                        int turnaroundTime = time - tab[i]->arrival;
                        int waitingTime = turnaroundTime - initialExecution;

                        totalTurnaroundTime += turnaroundTime;
                        totalWaitingTime += waitingTime;

                        printf("\033[1;34m \tP%d | Turnaround Time: %d | Waiting Time: %d \033[0m \n", tab[i]->pid, turnaroundTime, waitingTime);

                        deleteFirstNodeAtIndex(tab, i);
                        stop++;
                        i=0;
                        s=0;
                    }
                }
                else {
                    i++;
                }
                printf("\n level= %d  i= %d  time = %d \n",level,i,time);
            }
        }
        time++;
        i=0;
    }

    float avgTurnaroundTime = (float)totalTurnaroundTime / n;
    float avgWaitingTime = (float)totalWaitingTime / n;

    printf("\n\n \033[1;32m Average Turnaround Time: %.2f \033[0m\n", avgTurnaroundTime);
    printf("\033[1;32m Average Waiting Time: %.2f \033[0m\n\n", avgWaitingTime);


    printf("\n\n");


    return E;
}
