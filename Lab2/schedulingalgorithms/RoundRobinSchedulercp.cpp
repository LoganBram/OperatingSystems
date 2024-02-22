#include "RoundRobinScheduler.h"
#include <iostream>
#include <vector>
std::vector<Process> Processed;

RoundRobinScheduler::RoundRobinScheduler(const std::queue<Process> &pass_processes, int pass_quantum)
{
    processes = pass_processes;
    quantum = pass_quantum;
}

void RoundRobinScheduler::schedule()
{
    vector<Process> processesVector;

    int originalSize = processes.size(); // Store the original size

    for (int i = 0; i < originalSize; i++)
    {
        Process p = processes.front(); // Access front of the queue
        processesVector.push_back(p);  // Push to the vector
        processes.pop();               // Pop the front element
    }


    //sort by arrival time
    for (int i = 0; i < originalSize; i++)
    {
        for (int j = 0; j < originalSize - i - 1; j++)
        {
            if (processesVector[j].arrivalTime > processesVector[j + 1].arrivalTime)
            {
                Process temp = processesVector[j];
                processesVector[j] = processesVector[j + 1];
                processesVector[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < originalSize; i++) {//push vector back to queue
        Process p = processesVector[i];
        processes.push(p);
    }

    int currentTime = 0;

    while (!processes.empty())
    {
        Process p = processes.front();
        processes.pop();

        p.waitTime += currentTime - p.lastExecuted;
        if (p.burstTime == p.remainingTime)
        {
            p.start = currentTime;
        }

        if (p.remainingTime > quantum)
        {
            p.remainingTime -= quantum;
            currentTime += quantum;
            p.cycles++;
            p.lastExecuted = currentTime;
            processes.push(p);
        }
        else
        {
            currentTime += p.remainingTime;
            p.finishTime = currentTime;
            p.remainingTime = 0;
            processed.push_back(p);
        }
    }
}

void RoundRobinScheduler::calculateAverageWaitTime()
{
    double totalWaitTime = 0;

    for (const Process &p : processed)
    {
        totalWaitTime += p.waitTime;
    }

    double avgWait = totalWaitTime / processed.size();
    std::cout << "Average wait time: " << avgWait << std::endl;
}

void RoundRobinScheduler::calculateAverageTurnAroundTime()
{
    double totalTurnaround = 0;

    for (const Process &p : processed)
    {
        totalTurnaround += p.finishTime - p.arrivalTime;
    }

    double avgTurn = totalTurnaround / processed.size();
    std::cout << "Average turnaround time: " << avgTurn << std::endl;
}

;
