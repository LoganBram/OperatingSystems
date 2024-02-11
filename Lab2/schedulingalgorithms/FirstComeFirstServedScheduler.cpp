#include <iostream>
#include <queue> // Include the <queue> header file

#include "FirstComeFirstServedScheduler.h"

void FirstComeFirstServedScheduler::schedule()
{
    

    int wait = 0;
    for (int i = 0; i < processes.size(); i++)
    {
        Process p = processes.front();
        p.waitTime = wait - p.arrivalTime;
        wait += p.burstTime;
        p.remainingTime = 0;
        processes.pop();
        processes.push(p);
        
        
    }
}

void FirstComeFirstServedScheduler::calculateAverageWaitTime()
{
    int totalWaitTime = 0;
    int count =0;
    queue<Process> copy = processes;
    while(!processes.empty())
    {
        Process process = processes.front();
        processes.pop();
        totalWaitTime += process.waitTime;

        count++;
    }
    double averageWaitTime = static_cast<double>(totalWaitTime) / count;
    std::cout << "Average wait time: " << averageWaitTime << std::endl;
    processes = copy;
    
    // Implementation of calculating average wait time
}

void FirstComeFirstServedScheduler::calculateAverageTurnAroundTime()
{
    // Implementation of calculating average turn around time
    int totalTurnAroundTime = 0;
    int count =0;
    while(!processes.empty())
    {
        Process process = processes.front();
        processes.pop();
        totalTurnAroundTime += process.waitTime + process.burstTime; //turnaround time = waiting time + burst time
        count++;
    }
    double averageTurnAroundTime = static_cast<double>(totalTurnAroundTime) / count;
    std::cout << "Average wait time: " << averageTurnAroundTime << std::endl;
}