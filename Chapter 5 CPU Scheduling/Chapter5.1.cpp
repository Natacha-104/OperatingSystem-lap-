// File: process_basics.cpp
// Compile: g++ -o process_basics process_basics.cpp -std=c++17

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>

struct Process
{
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int priority;

    Process(int id, int at, int bt, int pr = 0)
        : pid(id), arrival_time(at), burst_time(bt),
          remaining_time(bt), completion_time(0),
          turnaround_time(0), waiting_time(0), priority(pr) {}
};

class ProcessScheduler
{
public:
    std::vector<Process> processes;

    void addProcess(int pid, int arrival, int burst, int priority = 0)
    {
        processes.emplace_back(pid, arrival, burst, priority);
    }

    // Compute scheduling using FCFS
    void computeFCFS()
    {
        if (processes.empty())
            return;

        // sort by arrival time (tie-breaker: pid)
        std::sort(processes.begin(), processes.end(),
                  [](const Process &a, const Process &b)
                  {
                      if (a.arrival_time == b.arrival_time)
                          return a.pid < b.pid;
                      return a.arrival_time < b.arrival_time;
                  });

        int current_time = 0;
        for (auto &p : processes)
        {
            if (current_time < p.arrival_time)
                current_time = p.arrival_time; // CPU idle until arrival

            p.completion_time = current_time + p.burst_time;
            p.turnaround_time = p.completion_time - p.arrival_time;
            p.waiting_time = p.turnaround_time - p.burst_time;

            current_time = p.completion_time;
        }
    }

    void displayProcesses()
    {
        std::cout << std::setw(5) << "PID" << std::setw(10) << "Arrival"
                  << std::setw(10) << "Burst" << std::setw(12) << "Completion"
                  << std::setw(12) << "Turnaround" << std::setw(10) << "Waiting\n";
        std::cout << std::string(60, '-') << "\n";

        for (const auto &p : processes)
        {
            std::cout << std::setw(5) << p.pid << std::setw(10) << p.arrival_time
                      << std::setw(10) << p.burst_time << std::setw(12) << p.completion_time
                      << std::setw(12) << p.turnaround_time << std::setw(10) << p.waiting_time << "\n";
        }
    }

    double calculateAverageWaitingTime()
    {
        if (processes.empty())
            return 0.0;
        int total = 0;
        for (const auto &p : processes)
        {
            total += p.waiting_time;
        }
        return static_cast<double>(total) / processes.size();
    }

    double calculateAverageTurnaroundTime()
    {
        if (processes.empty())
            return 0.0;
        int total = 0;
        for (const auto &p : processes)
        {
            total += p.turnaround_time;
        }
        return static_cast<double>(total) / processes.size();
    }
};

// Demo main function
int main()
{
    ProcessScheduler scheduler;

    // Example processes
    scheduler.addProcess(1, 0, 7);
    scheduler.addProcess(2, 2, 4);
    scheduler.addProcess(3, 4, 1);
    scheduler.addProcess(4, 5, 4);

    std::cout << "Basic Process Structure Demo (FCFS)\n";
    std::cout << "===================================\n";

    // compute schedule (FCFS) before displaying
    scheduler.computeFCFS();
    scheduler.displayProcesses();

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nAverage Waiting Time   : " << scheduler.calculateAverageWaitingTime() << "\n";
    std::cout << "Average Turnaround Time: " << scheduler.calculateAverageTurnaroundTime() << "\n";

    return 0;
}
