#include <stdio.h>
#include <stdlib.h>

int processNumber;
struct executionInterval {
    int Max;
    int min;
};
struct arrivedInterval {
    int Max;
    int min;
};
struct priorityInterval {
    int Max;
    int min;
};
typedef struct executionInterval ExecInterval;
typedef struct arrivedInterval ArrivedInterval;
typedef struct priorityInterval PriorityInterval;

int getProcessNumber(){ // pour l'acquisition de nmbr de process
    printf("How many process would you like to execute: \n");
    scanf("%d", &processNumber);
    while(processNumber > 10){
        printf("Process number must be lesser than 10\n Try Again: ");
        scanf("%d", &processNumber);
    }
    printf("This is the process number you entered: %d \n", processNumber);
    return processNumber;
};

ExecInterval getExecutionTimeInterval(){ // pour l'acquisition de l'interval du temps d'execution
    ExecInterval e;
    int tmp;
    printf("Execution time maximum (seconds):\n");
    scanf("%d", &e.Max);
    printf("Execution time minimum (seconds):\n");
    scanf("%d", &e.min);

    // besh el max dima tkoun feha el valeur el akber.
    if(e.Max<e.min){
        tmp = e.Max;
        e.Max = e.min;
        e.min = tmp;
    }
    printf("Minumum Execution Time: %d | Maximum Execution Time: %d\n", e.min, e.Max);

    return e;
}

ArrivedInterval getArrivedTimeInterval(){
    ArrivedInterval a;
    int tmp;
    printf("Arrived time maximum (seconds):\n");
    scanf("%d", &a.Max);
    printf("Arrived time minimum (seconds):\n");
    scanf("%d", &a.min);

    // besh el max dima tkoun feha el valeur el akber.
    if(a.Max<a.min){
        tmp = a.Max;
        a.Max = a.min;
        a.min = tmp;
    }
    printf("Minumum Arrived Time: %d | Maximum Arrived Time: %d\n", a.min, a.Max);
    return a;
}

PriorityInterval getPriorityInterval(){
    PriorityInterval p;
    int tmp;
    printf("Priority maximum:\n");
    scanf("%d", &p.Max);
    printf("Priority minimum:\n");
    scanf("%d", &p.min);

    // besh el max dima tkoun feha el valeur el akber.
    if(p.Max<p.min){
        tmp = p.Max;
        p.Max = p.min;
        p.min = tmp;
    }
    printf("Minumum Priority: %d | Maximum Priority: %d\n", p.min, p.Max);
    return p;
}
/* void generateProcess(int nmbr, ExecInterval e, ArrivedInterval a, PriorityInterval p) {
    printf("------------------------------------------------------------\n");
    printf("| Process   | Execution Time | Arrival Time  | Priority\n");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < nmbr; i++) {
        int executionTime = e.min + (rand() % e.Max);
        int arrivalTime = a.min + (rand() % a.Max);
        int priority = p.min + (rand()%p.Max);
        printf("| Process%d  | %-14d | %-13d  |%-9d\n", i, executionTime, arrivalTime, priority);
    }

    printf("------------------------------------------------------------\n");
} */
void generateProcess(int nmbr, ExecInterval e, ArrivedInterval a, PriorityInterval p, FILE* file) {
    fprintf(file, "------------------------------------------------------------\n");
    fprintf(file, "| Process   | Execution Time | Arrival Time  | Priority\n");
    fprintf(file, "------------------------------------------------------------\n");

    for (int i = 0; i < nmbr; i++) {
        int executionTime = e.min + (rand() % e.Max);
        int arrivalTime = a.min + (rand() % a.Max);
        int priority = p.min + (rand() % p.Max);
        fprintf(file, "| Process%d  | %-14d | %-13d  |%-9d\n", i, executionTime, arrivalTime, priority);
    }

    fprintf(file, "------------------------------------------------------------\n");
}

int main()
{
    printf("-------------------Process Number---------------------\n");
    getProcessNumber();
    printf("\n");
    printf("----------------Execution Time Interval---------------\n");
    ExecInterval executionInterval = getExecutionTimeInterval();
    printf("\n");
    printf("----------------Arrival Time Interval-----------------\n");
    ArrivedInterval arrivedInterval = getArrivedTimeInterval();
    printf("\n");
    printf("-------------------Priority Interval------------------\n");
    PriorityInterval priorityInterval = getPriorityInterval();
    printf("\n");
    printf("\n");
    printf("\n");
    FILE* file = fopen("process_table.txt", "w"); // Open the file for writing
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }
    generateProcess(processNumber, executionInterval, arrivedInterval, priorityInterval, file);
    printf("Process File Generated");
    system("code process_table.txt &");
    return 0;
}