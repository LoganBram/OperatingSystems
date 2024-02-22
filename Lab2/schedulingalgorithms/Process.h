#pragma once

#ifndef PROCESS_H // ADD THIS

#define PROCESS_H // ADD THIS

struct Process

{

    int id; // Process ID

    int burstTime; // CPU Burst Time

    int arrivalTime;

    int waitTime;

    int remainingTime;

    int cycles;

    int lastExecuted;

    int finishTime = 0;

    int time_ran;

    int start;

    Process(int id, int burstTime) : id(id), burstTime(burstTime) {}

    Process(int id, int burstTime, int arrivalTime) : id(id), burstTime(burstTime), arrivalTime(arrivalTime) {}
};

#endif // ADD THIS