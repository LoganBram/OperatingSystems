#ifndef ROUNDROBINSCHEDULER_H
#define ROUNDROBINSCHEDULER_H

#include <queue>
#include "Process.h"
#include "CPUScheduler.h"
using namespace std;

class RoundRobinScheduler : public CPUScheduler
{
private:
    int quantum;
    queue<Process> processes; // Declare processes as a member variable
public:
    RoundRobinScheduler(const queue<Process> &pass_processes, int pass_quantum); //use this for consturctor
    void schedule() override;
    void calculateAverageWaitTime() override;
    void calculateAverageTurnAroundTime() override;
};

#endif
