#include <iostream>
#include "FirstComeFirstServedScheduler.h"

void FirstComeFirstServedScheduler::schedule()
{
    while (!processes.empty())
    {
        Process process = processes.front();
        processes.pop();
    }
}

void FirstComeFirstServedScheduler::calculateAverageWaitTime()
{
    int totalWaitTime = 0;
    int count =0;
    for (int i = 0; i < processes.size(); i++)
    {
        Process process = processes.front();
        processes.pop();
        totalWaitTime += process.waitTime;

        count++;
    }
    double averageWaitTime = static_cast<double>(totalWaitTime) / count;
    std::cout << "Average wait time: " << averageWaitTime << std::endl;
    
    // Implementation of calculating average wait time
}

void FirstComeFirstServedScheduler::calculateAverageTurnAroundTime()
{
    // Implementation of calculating average turn around time
    int totalTurnAroundTime = 0;
    int count =0;
    for (int i = 0; i < processes.size(); i++)
    {
        Process process = processes.front();
        processes.pop();
        totalTurnAroundTime += process.waitTime + process.burstTime; //turnaround time = waiting time + burst time
        count++;
    }
    double averageTurnAroundTime = static_cast<double>(totalTurnAroundTime) / count;
    std::cout << "Average wait time: " << averageTurnAroundTime << std::endl;
}