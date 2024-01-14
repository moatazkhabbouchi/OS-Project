cmake_minimum_required(VERSION 3.26)
project(SE_Project_Process_Scheduling C)

set(CMAKE_C_STANDARD 11)

add_executable(SE_Project_Process_Scheduling main.c
        "Queue/QueueManipulation.c"
        "CPU_Scheduling_Algorithms/FIFO/FIFO.c"
        "CPU_Scheduling_Algorithms/FIFO/FIFO.h"
        "CPU_Scheduling_Algorithms/RR/RR.h"
        "CPU_Scheduling_Algorithms/RR/RR.c"
        GanttChart/GanttChart.h
        GanttChart/GanttChart.c
        "CPU_Scheduling_Algorithms/SRT/SRT.h"
        "CPU_Scheduling_Algorithms/SRT/SRT.c"
        "CPU_Scheduling_Algorithms/Priority/Priority.h"
        "CPU_Scheduling_Algorithms/Priority/Priority.c"
        "CPU_Scheduling_Algorithms/Multilevel/MultiLevel.h"
        "CPU_Scheduling_Algorithms/Multilevel/MultiLevel.c")
