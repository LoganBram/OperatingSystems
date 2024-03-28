#include <iostream>
#include <queue> // Include the <queue> header file


#include "FirstComeFirstServedScheduler.h"
FirstComeFirstServedScheduler::FirstComeFirstServedScheduler(const queue<Process> &pass_processes, int pass_quantum)
{
    processes = pass_processes;
    quantum = pass_quantum;
}
void FirstComeFirstServedScheduler::schedule()
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
    for (int i = 0; i < processes.size(); i++)
    {
        Process p = processes.front();
        processes.pop();
        totalWaitTime += p.waitTime;
        count++;
        processes.push(p);
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
        Process p = processes.front();
        processes.pop();
        totalTurnAroundTime += p.waitTime + p.burstTime; //turnaround time = waiting time + burst time
        count++;
    }
    double averageTurnAroundTime = static_cast<double>(totalTurnAroundTime) / count;
    std::cout << "Average turn around time: " << averageTurnAroundTime << std::endl;
}