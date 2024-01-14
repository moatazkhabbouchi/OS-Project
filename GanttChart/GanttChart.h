#ifndef SE_PROJECT_PROCESS_SCHEDULING_GANTTCHART_H
#define SE_PROJECT_PROCESS_SCHEDULING_GANTTCHART_H

#include "../Queue/QueueManipulation.h"

enum AnsiColor {
    ANSI_RESET = 0,
    ANSI_BLUE,
    ANSI_GREEN,
    ANSI_RED,
    ANSI_YELLOW,
    ANSI_MAGENTA,
    ANSI_CYAN
};

void printColoredText(char *text, enum AnsiColor color);

void displayGanttChart(struct exec* GanttChart);

#endif
