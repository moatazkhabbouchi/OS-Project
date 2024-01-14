#ifndef SE_PROJECT_PROCESS_SCHEDULING_MULTILEVEL_H
#define SE_PROJECT_PROCESS_SCHEDULING_MULTILEVEL_H

#include "../../Queue/QueueManipulation.h"

int priorityOcc(liste L);
struct exec* MultiLevel(liste L,int n,int quantum, int* execT);

#endif
