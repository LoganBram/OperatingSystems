#include "RoundRobinScheduler.h"
RoundRobinScheduler::RoundRobinScheduler(const queue<Process> &pass_processes, int pass_quantum) {
    processes = pass_processes;
    quantum = pass_quantum;
}



void RoundRobinScheduler::schedule()
{
    // TODO: Implementation of Round Robin scheduling
    throw "Not implemented"; // Remove this line
}

void RoundRobinScheduler::calculateAverageWaitTime()
{
    // TODO: Implementation of calculating average wait time
    throw "Not implemented"; // Remove this line
}

void RoundRobinScheduler::calculateAverageTurnAroundTime()
{
    // TODO: Implementation of calculating average turn around time
    throw "Not implemented"; // Remove this line
}