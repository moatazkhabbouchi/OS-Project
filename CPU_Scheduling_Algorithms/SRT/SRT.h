#ifndef SE_PROJECT_PROCESS_SCHEDULING_SRT_H
#define SE_PROJECT_PROCESS_SCHEDULING_SRT_H

#include "../../Queue/QueueManipulation.h"

struct exec* SRT(liste processes, int n, int* execT);

liste minimum(liste L, int time);

#endif
