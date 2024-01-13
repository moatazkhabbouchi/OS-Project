#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

typedef struct process* procList; 
struct process{
    int pid, arrivalTime, executionTime, priority;
    procList next;
};

// Method to add processes to the list.
procList addProc(procList head, procList e){
    if(head == NULL){
        head = e;
        return head;
    }
    e->next = head;
    head = e;
    return head;    
}

void extractProcess(){
    FILE *file = fopen("process_table.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[256]; // Adjust the size as needed

    // Read lines from the file using fgets
    while (fgets(line, sizeof(line), file) != NULL) {
        char *token;
        char *delimiter = ",";
        char *values[4]; // Array to store the four values

        token = strtok(line, delimiter);
        int i = 0;
        while (token != NULL && i < 4) {
            values[i++] = token;
            token = strtok(NULL, delimiter);
        }

        // Store values in separate variables
        if (i == 4) {
            char *value1 = values[0];
            char *value2 = values[1];
            char *value3 = values[2];
            char *value4 = values[3];

            // Use the values as needed
            printf("Values: %s, %s, %s, %s\n", value1, value2, value3, value4);
     }
    }

    // Close the file when done
    fclose(file);
}

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

    for (int i = 0; i < nmbr; i++) {
        int executionTime = e.min  + (rand() % (e.Max - e.min + 1));
        int arrivalTime = a.min + (rand() % (a.Max - a.min + 1));
        int priority = p.min + (rand() % (p.Max - p.min +1));
        fprintf(file, "P%d, %d, %d, %d \n", i, executionTime, arrivalTime, priority);
    }
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
    fclose(file);
    printf("Process File Generated");
    extractProcess();
    system("code process_table.txt &");
    return 0;
}