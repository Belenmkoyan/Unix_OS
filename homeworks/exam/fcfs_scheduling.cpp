#include <iostream>
#include <queue>

struct Process {
    size_t burst_time;
    int waitingTime;
    int arrivalTime;
    pid_t pid;

    Process(pid_t id, size_t bt) : pid(id), burst_time(bt), waitingTime(0) {}

};

class Scheduler {
public:
    Scheduler() {
        std::cout << "Scheduler created" << std::endl;
    }

    void add_process(pid_t id, size_t bt) {
        Process p(id, bt);
        process_queue.push(p);
    }

    void schedule() {
        int currentTime = 0;
        int totalWaitingTime = 0;
        int totalTurnaroundTime = 0;

        std::cout << "Scheduling processes using FCFS..." << std::endl;
        int processCount = process_queue.size();

        while (!process_queue.empty()) {
            Process p = process_queue.front();
            process_queue.pop();

            p.waitingTime = currentTime;
            int turnaroundTime = p.waitingTime + p.burst_time;

            totalWaitingTime += p.waitingTime;
            totalTurnaroundTime += turnaroundTime;

            std::cout << "Process " << p.pid << " | Burst Time: " << p.burst_time << " | Waiting Time: " 
                        << p.waitingTime << " | Turnaround Time: " << turnaroundTime << std::endl;

            currentTime += p.burst_time;
        }
    }

private:
    std::queue<Process> process_queue;
};


int main() {
    Scheduler scheduler;

    scheduler.add_process(1, 5);
    scheduler.add_process(2, 8);
    scheduler.add_process(3, 3);

    scheduler.schedule();
    return 0;
}
