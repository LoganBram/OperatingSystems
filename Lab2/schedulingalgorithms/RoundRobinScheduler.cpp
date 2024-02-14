#include "RoundRobinScheduler.h"
#include <iostream>
#include <vector>

RoundRobinScheduler::RoundRobinScheduler(const std::queue<Process> &pass_processes, int pass_quantum)
{
    processes = pass_processes;
    quantum = pass_quantum;
}

void RoundRobinScheduler::schedule()
{

    int currentTime = 0;
    std::queue<Process> tempQueue = processes; // work with a copy to preserve original queue
    std::vector<Process> processed;

    if (p.remainingTime > quantum)
    {
        p.remainingTime -= quantum;
        currentTime += quantum;
        p.cycles += 1;
    }
    if (p.remainingTime == quantum)
    {
        p.lastexecuted = currentTime;
        p.remainingTime == 0;
        currentTime += quantum;
    }
    else
    {
        p.lastexecuted = currentTime;
        p.remainingTime == 0;
        currentTime += p.remainingTime;
        p.finishTime = currentTime;
    }
}

void RoundRobinScheduler::calculateAverageWaitTime()
{
}

void RoundRobinScheduler::calculateAverageTurnAroundTime()
{
}