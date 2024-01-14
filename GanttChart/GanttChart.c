#include <stdio.h>
#include "GanttChart.h"


void printColoredText(char *text, enum AnsiColor color) {
    printf("\033[1;%dm %s \033[0m", 30 + color, text);
}

void displayGanttChart(struct exec* GanttChart) {
    printf("\033[1;34m \tGantt Chart: \033[0m\n");
    printf("| ");

    while (GanttChart != NULL) {
        printColoredText("P", GanttChart->id % 6);
        printf("%d ", GanttChart->id);

        for (int i = 0; i < (GanttChart->end - GanttChart->start); i++) {
            printColoredText("*", GanttChart->id % 6);
        }
        printf(" | ");

        GanttChart = GanttChart->next;
    }
    printf("\n");
}
