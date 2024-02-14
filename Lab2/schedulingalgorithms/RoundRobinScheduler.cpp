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
    std::queue<Process> tempQueue = processes; // Work with a copy to preserve original queue
    processes = {};                            // Clear the original queue to start fresh

    while (!tempQueue.empty())
    {
        Process currentProcess = tempQueue.front();
        tempQueue.pop();

        if (currentProcess.remainingTime <= 0)
        {
            continue; // Skip processes that are already completed
        }

        if (currentProcess.remainingTime > quantum)
        {
            currentTime += quantum;
            currentProcess.remainingTime -= quantum;
            currentProcess.waitTime += quantum; // Accumulate wait time for each cycle
            tempQueue.push(currentProcess);     // Requeue for further processing
        }
        else
        {
            currentTime += currentProcess.remainingTime;
            currentProcess.waitTime += currentTime - currentProcess.burstTime - currentProcess.waitTime; // Correct wait time calculation
            currentProcess.remainingTime = 0;
            completedProcesses.push_back(currentProcess); // Store completed process
        }
    }
}

void RoundRobinScheduler::calculateAverageWaitTime()
{
    double totalWaitTime = 0;
    for (const Process &p : completedProcesses)
    {
        totalWaitTime += p.waitTime;
    }

    double averageWaitTime = completedProcesses.empty() ? 0 : totalWaitTime / completedProcesses.size();
    std::cout << "Average Wait Time: " << averageWaitTime << std::endl;
}

void RoundRobinScheduler::calculateAverageTurnAroundTime()
{
    double totalTurnAroundTime = 0;
    for (const Process &p : completedProcesses)
    {
        totalTurnAroundTime += p.waitTime + p.burstTime;
    }

    double averageTurnAroundTime = completedProcesses.empty() ? 0 : totalTurnAroundTime / completedProcesses.size();
    std::cout << "Average Turnaround Time: " << averageTurnAroundTime << std::endl;
}

;