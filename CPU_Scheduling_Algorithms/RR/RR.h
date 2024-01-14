#ifndef SE_PROJECT_PROCESS_SCHEDULING_RR_H
#define SE_PROJECT_PROCESS_SCHEDULING_RR_H

#include "../../Queue/QueueManipulation.h"

struct exec* RR(liste processes, int quantum, int* execT);

#endif
