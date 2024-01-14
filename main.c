#define NUM_ALGORITHMS 5
#define MAX_ATTEMPTS 4

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Queue/QueueManipulation.h"
#include "CPU_Scheduling_Algorithms/FIFO/FIFO.h"
#include "GanttChart/GanttChart.h"
#include "CPU_Scheduling_Algorithms/RR/RR.h"
#include "CPU_Scheduling_Algorithms/SRT/SRT.h"
#include "CPU_Scheduling_Algorithms/Priority/Priority.h"
#include "CPU_Scheduling_Algorithms/Multilevel/MultiLevel.h"


typedef struct {
    int min;
    int max;
} Interval;

int generateRandomNumber(Interval interval) {
    return interval.min + rand() % (interval.max - interval.min + 1);
}

void generateProcess(int processNumber, Interval arrivalInterval, Interval executionInterval, Interval priorityInterval, FILE *file) {
    srand(time(NULL));

    for (int i = 0; i < processNumber; i++) {
        int arrival_time = generateRandomNumber(arrivalInterval);
        int execution_time = generateRandomNumber(executionInterval);
        int priority = generateRandomNumber(priorityInterval);

        fprintf(file, "Process %d: Arrival Time %d, Execution Time %d, Priority %d\n", i + 1, arrival_time, execution_time, priority);
    }
}

typedef struct {
    const char* name;
    const char* hint;
} Algorithm;

Algorithm ALGORITHMS[NUM_ALGORITHMS] = {
        {"FIFO", "This algorithm uses a simple rule: first come, first served."},
        {"RR", "This algorithm assigns a fixed time unit per process and cycles through them."},
        {"Multilevel", "This algorithm organizes processes into multiple queues with different priority levels."},
        {"Priority", "This algorithm assigns priority levels to processes and executes the highest priority process first."},
        {"SRT", "This algorithm schedules the process with the smallest total remaining processing time first."},
};

void printWelcomeMessage() {
    printf("\033[1;34m==========================================\n");
    printf("      Welcome to the Algorithm Guessing Game!\n");
    printf("==========================================\033[0m\n");
    printf("You are given an algorithm name. Guess all the algorithms using the provided hints.\n");
    printf("You have %d attempts for each algorithm.\n\n", MAX_ATTEMPTS);
    printf("The choices can be \033[1;32mFIFO\033[0m, \033[1;33mRR\033[0m, \033[1;36mPriority\033[0m, \033[1;31mSRT\033[0m, \033[1;35mMultilevel\033[0m\n");
}

void printHangman(int attemptsLeft) {
    switch (attemptsLeft) {
        case 0:
            printf("   _______\n");
            printf("   |     |\n");
            printf("         |\n");
            printf("         |\n");
            printf("         |\n");
            printf("         |\n");
            break;
        case 1:
            printf("   _______\n");
            printf("   |     |\n");
            printf("   O     |\n");
            printf("         |\n");
            printf("         |\n");
            printf("         |\n");
            break;
        case 2:
            printf("   _______\n");
            printf("   |     |\n");
            printf("   O     |\n");
            printf("   |     |\n");
            printf("         |\n");
            printf("         |\n");
            break;
        case 3:
            printf("   _______\n");
            printf("   |     |\n");
            printf("   O     |\n");
            printf("  /|\\    |\n");
            printf("  / \\    |\n");
            printf("         |\n");
            break;
    }
}

int main() {

    int prefer;
    do {
        printf("If you want to play a knowledge game before accessing to scheduler, tap 1 else tap 0: ");
        scanf("%d", &prefer);
    } while ((prefer != 1) && (prefer != 0));


    if (prefer == 1) {
        srand(time(NULL));

        printWelcomeMessage();

        for (int algorithmIndex = 0; algorithmIndex < NUM_ALGORITHMS; ++algorithmIndex) {
            Algorithm selectedAlgorithm = ALGORITHMS[algorithmIndex];
            int attemptsLeft = MAX_ATTEMPTS;

            printf("==========================================\n");
            printf("Algorithm %d: %s\n", algorithmIndex + 1, selectedAlgorithm.hint);

            while (attemptsLeft > 0) {
                char userGuess[20];
                printf("Your guess: \n");
                scanf("%s", userGuess);

                if (strcmp(userGuess, selectedAlgorithm.name) == 0) {
                    printf("Correct! Well done.\n\n");
                    break;
                } else {
                    printf("Incorrect. Try again. %d attempts left.\n", attemptsLeft - 1);
                    printHangman(MAX_ATTEMPTS - attemptsLeft);
                    attemptsLeft--;
                }
            }

            if (attemptsLeft == 0) {
                printf("Out of attempts. The correct answer was %s.\n\n", selectedAlgorithm.name);
            }
        }

        printf("  ===============================================\n");
        printf("   Game over. You've guessed all the algorithms.\n");
        printf("  ===============================================\n");

    }


    int processNumber, choice;
    Interval arrivalTimeInterval, executionTimeInterval, priorityInterval;
    srand(time(0));


    printf("\x1b[38;2;3;174;198m __          __  _                            _                             _____                                _____      _              _       _           \x1b[0m\n");
    printf("\x1b[38;2;3;174;198m\\ \\        / / | |                          | |                           |  __ \\                              / ____|    | |            | |     | |          \x1b[0m\n");
    printf("\x1b[38;2;3;174;198m \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___  | |_ ___     ___  _   _ _ __  | |__) | __ ___   ___ ___  ___ ___  | (___   ___| |__   ___  __| |_   _| | ___ _ __ \x1b[0m\n");
    printf("\x1b[38;2;3;174;198m   \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\   / _ \\| | | | '__| |  ___/ '__/ _ \\ / __/ _ \\/ __/ __|  \\___ \\ / __| '_ \\ / _ \\/ _` | | | | |/ _ \\ '__|\x1b[0m\n");
    printf("\x1b[38;2;3;174;198m    \\  /\\  /  __/ | (_| (_) | | | | | |  __/ | || (_) | | (_) | |_| | |    | |   | | | (_) | (_|  __/\__ \\__ \\  ____) | (__| | | |  __/ (_| | |_| | |  __/ |   \x1b[0m\n");
    printf("\x1b[38;2;3;174;198m    \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/   \\___/ \\__,_|_|    |_|   |_|  \\___/ \\___\___||___/___/ |_____/ \\___|_| |_|\\___|\\__,_|\\__,_|_|\\___|_|   \x1b[0m\n");


    printf("\n\n");

    do {
        printf("1- Please type the number of process you want to simulate: ");
        scanf("%d", &processNumber);
    } while (processNumber <= 0);
    printf("\n");

    printf("2- Now choose the interval of Arrival Time of your process:\n");
    do{
        printf("\tMin: ");
        scanf("%d", &arrivalTimeInterval.min);
    } while (arrivalTimeInterval.min < 0);
    do {
        printf("\tMax: ");
        scanf("%d", &arrivalTimeInterval.max);
    } while (arrivalTimeInterval.max <= arrivalTimeInterval.min);
    printf("\n");

    printf("3- Next choose the interval of Execution Time of your process:\n");
    do {
        printf("\tMin: ");
        scanf("%d", &executionTimeInterval.min);
    } while (executionTimeInterval.min < 0);
    do {
        printf("\tMax: ");
        scanf("%d", &executionTimeInterval.max);
    } while (executionTimeInterval.max < executionTimeInterval.min);
    printf("\n");

    printf("4- Finally, choose the interval of Priority of your process:\n");
    do {
        printf("\tMin: ");
        scanf("%d", &priorityInterval.min);
    } while (priorityInterval.min < 0);
    do {
        printf("\tMax: ");
        scanf("%d", &priorityInterval.max);
    } while (priorityInterval.max < priorityInterval.min);
    printf("\n");


    FILE *file = fopen("test.txt", "w");
    if (file == NULL) {
        perror("Error when opening file");
        exit(1);
    }

    generateProcess(processNumber, arrivalTimeInterval, executionTimeInterval, priorityInterval, file);
    printf("Process File generated successfully !\n\n\n");
    fclose(file);
    system("gedit test.txt &");


    liste L = NULL;
    L = collectProcesses(L);
     bubbleSort(&L, processNumber);

     printf("\033[38;2;3;174;198m Sorted list of processes based on arrival time:\033[0m\n");
     printList(L);


    do {
        printf("\nMenu: Scheduling Algorithms \n");
        printf("\033[1;34m \t\t[1] FIFO  \033[0m\n");
        printf("\033[38;2;249;16;16m \t\t[2] Round Robin \033[0m\n");
        printf("\033[38;2;2;156;142m \t\t[3] SRT  \033[0m\n");
        printf("\033[38;2;138;43;226m \t\t[4] Priority  \033[0m\n");
        printf("\033[38;2;255;207;1m \t\t[5] MultiLevel  \033[0m\n");
        printf("\t\t[0] Quit\n\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        printf("\n");
        printf("\n********************************************************************************************************************************************************\n");

        liste L3 = NULL;
        L3 = collectProcesses(L3);
        bubbleSort(&L3, processNumber);


        switch (choice) {
            case 1: {
                printf("\033[1;34m 1- FIFO Scheduling: \033[0m\n\n");

                struct exec *E_FIFO = FIFO(L3);

                FILE *file = fopen("results.txt", "w");
                if (file == NULL) {
                    perror("Error when opening file");
                    exit(1);
                }
                struct exec* tmp=E_FIFO;
                while (tmp != NULL) {

                    fprintf(file, "%d,%d,%d\n",tmp->id,tmp->start,tmp->end);
                    tmp=tmp->next;
                }

                fclose(file);

                displayGanttChart(E_FIFO);

                system("node ./CProject/test.js ");

                printf("\n********************************************************************************************************************************************************\n");
                break;
            }
            case 2: {
                printf("\n\033[38;2;249;16;16m 2- Round Robin Scheduling: \033[0m\n\n");
                int quantum;
                printf("Enter the time quantum for Round Robin: ");
                scanf("%d", &quantum);

                int* execT = getExecutionTimes(L3,processNumber);
                struct exec *E_RR = RR(L3, quantum, execT);

                FILE *file = fopen("results.txt", "w");
                if (file == NULL) {
                    perror("Error when opening file");
                    exit(1);
                }
                struct exec* tmp=E_RR ;
                while (tmp != NULL) {

                    fprintf(file, "%d,%d,%d\n",tmp->id,tmp->start,tmp->end);
                    tmp=tmp->next;
                }

                fclose(file);

                displayGanttChart(E_RR);

                system("node ./CProject/test.js ");

                printf("\n********************************************************************************************************************************************************\n");
                break;
            }
            case 3: {
                printf("\n\033[38;2;2;156;142m 3- SRT Scheduling: \033[0m\n\n");

                int* execT = getExecutionTimes(L3,processNumber);
                struct exec *E_SRT = SRT(L3, processNumber, execT);

                FILE *file = fopen("results.txt", "w");
                if (file == NULL) {
                    perror("Error when opening file");
                    exit(1);
                }
                struct exec* tmp=E_SRT ;
                while (tmp != NULL) {

                    fprintf(file, "%d,%d,%d\n",tmp->id,tmp->start,tmp->end);
                    tmp=tmp->next;
                }

                fclose(file);

                displayGanttChart(E_SRT);

                system("node ./CProject/test.js ");

                printf("\n********************************************************************************************************************************************************\n");
                break;
            }
            case 4: {
                printf("\033[38;2;138;43;226m 4- Priority Scheduling: \033[0m\n");

                int* execT = getExecutionTimes(L3,processNumber);
                struct exec *E_PR = PR(L3, processNumber, execT);

                FILE *file = fopen("results.txt", "w");
                if (file == NULL) {
                    perror("Error when opening file");
                    exit(1);
                }
                struct exec* tmp=E_PR ;
                while (tmp != NULL) {
                    fprintf(file, "%d,%d,%d\n",tmp->id,tmp->start,tmp->end);
                    tmp=tmp->next;
                }

                fclose(file);

                displayGanttChart(E_PR);

                system("node ./CProject/test.js ");

                printf("\n********************************************************************************************************************************************************\n");
                break;
            }
            case 5: {
                printf("\033[38;2;255;207;1m 5- MultiLevel Scheduling: \033[0m\n");

                int quantum;
                int* execT = getExecutionTimes(L3,processNumber);

                printf("Enter the time quantum: ");
                scanf("%d", &quantum);

                struct exec *E_M = MultiLevel(L3, processNumber,quantum, execT);

                FILE *file = fopen("results.txt", "w");
                if (file == NULL) {
                    perror("Error when opening file");
                    exit(1);
                } else{
                    struct exec* tmp=E_M;
                    while (tmp != NULL) {
                        fprintf(file, "%d,%d,%d\n",tmp->id,tmp->start,tmp->end);
                        tmp=tmp->next;
                    }
                }

                fclose(file);

                displayGanttChart(E_M);

                system("node ./CProject/test.js ");
                printf("\n********************************************************************************************************************************************************\n");
                break;
            }
            case 0: {
                break;
            }
            default: {
                printf("\033[1;34m 1- FIFO Scheduling: \033[0m\n\n");

                struct exec *E_FIFO = FIFO(L3);

                FILE *file = fopen("results.txt", "w");
                if (file == NULL) {
                    perror("Error when opening file");
                    exit(1);
                }
                struct exec* tmp=E_FIFO;
                while (tmp != NULL) {

                    fprintf(file, "%d,%d,%d\n",tmp->id,tmp->start,tmp->end);
                    tmp=tmp->next;
                }

                fclose(file);

                displayGanttChart(E_FIFO);

                system("node ./CProject/test.js ");

                printf("\n********************************************************************************************************************************************************\n");
                break;

            }
        }
    } while (choice != 0);

    return 0;

}