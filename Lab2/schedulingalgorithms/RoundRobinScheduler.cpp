#include "RoundRobinScheduler.h"
#include <iostream>
#include <vector>
RoundRobinScheduler::RoundRobinScheduler(const queue<Process> &pass_processes, int pass_quantum)
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

    int time = processes.front().arrivalTime;
    bool done = true;
    int burst_time;
    while (done)
    {
        Process p = processes.front();
        if (p.remainingTime >0) {

            if (p.remainingTime > quantum) {
                burst_time = quantum;
            }
            else
            {
                burst_time = p.remainingTime;
            }



            if (p.remainingTime == p.burstTime) {
                p.start = time;
                p.remainingTime -= burst_time;
            }

            if (p.remainingTime > quantum) {
                p.remainingTime -= quantum;
                p.time_ran += quantum;
            }
            p.remainingTime -=burst_time;
            if(p.remainingTime == 0){//remaining time  == 0
                p.remainingTime = 0;
                p.waitTime = time - p.start - p.time_ran;
                p.finishTime = time + burst_time;
            }
            time += burst_time;

        }
        processes.pop();
        processes.push(p);
        for (int i=0; i<processes.size(); i++) {
            Process k = processes.front();
            if (k.remainingTime == 0){
                done = false;
            } else{
                done = true;
                break;
            }
            processes.pop();
            processes.push(k);
        }
    }
}

void RoundRobinScheduler::calculateAverageWaitTime()
{
    float totalWaitTime = 0;
    float size = static_cast<float>(processes.size());

    for (int i = 0; i<processes.size();i++)
    {
        Process p = processes.front();
        totalWaitTime += p.waitTime;
        processes.push(p);
        processes.pop();
    }

    float avgWait = totalWaitTime / size;
    std::cout << "Average wait time: " << avgWait << std::endl;
}

void RoundRobinScheduler::calculateAverageTurnAroundTime()
{
    float totalTurnaround = 0;
    float size = static_cast<float>(processes.size());

    for (int i = 0; i<processes.size();i++)
    {
        Process p = processes.front();
        totalTurnaround += p.finishTime - p.arrivalTime;
        processes.push(p);
        processes.pop();
    }

    float avgTurn = totalTurnaround / size;
    std::cout << "Average turnaround time: " << avgTurn << std::endl;
}

;
