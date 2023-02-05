#include <bits/stdc++.h>
using namespace std;
#define ll long long

class Process
{
public:
    int pid;
    int priority;
    int arrivalTime;
    int waitingTime;
    int responseTime;
    int turnaroundTime;

    list<pair<char, int>> Burst;
    Process()
    {
        pid = -1;
    }
    Process(int pid, int priority, int arrivalTime)
    {
        this->pid = pid;
        this->priority = priority;
        this->arrivalTime = arrivalTime;
        responseTime = -1;
        waitingTime = 0;
    }

    void takeBurst(char type, int time)
    {
        Burst.push_back({type, time});
    }
};

class FCFS
{
    int numOfProcess;
    int quantumValue;
    int currentTime;
    vector<Process> processes;
    queue<Process> fpq;
    queue<Process> fiq;
    queue<Process> foq;

public:
    FCFS(int numOfProcess, int quantumValue)
    {
        this->numOfProcess = numOfProcess;
        this->quantumValue = quantumValue;
        currentTime = 0;
    }

    void addProcess(Process p)
    {
        fpq.push(p);
    }

    void schedule()
    {
        int currentTime = fpq.front().arrivalTime;

        int pid1;

        while (fpq.size() || fiq.size() || foq.size())
        {
            pid1 = -1;
            // cout << endl
            //      << currentTime << "-" << currentTime + 1 << "->";

            if (!fpq.empty())
            {
                Process &p = fpq.front();
                // cout << "fpq" << p.pid << " ";
                if (p.responseTime == -1)
                    p.responseTime = currentTime - p.arrivalTime;

                p.waitingTime--;
                p.Burst.front().second--;
                if (p.Burst.front().second == 0)
                {
                    p.Burst.pop_front();
                    if (p.Burst.size() == 0)
                    {
                        // process completed
                        p.turnaroundTime = currentTime + 1 - p.arrivalTime;
                        p.waitingTime += p.turnaroundTime;
                        processes.push_back(p);
                    }
                    else if (p.Burst.front().first == 'I')
                        fiq.push(p);
                    else
                        foq.push(p);
                    pid1 = p.pid;
                    fpq.pop();
                }
            }

            if (!fiq.empty() and pid1 != fiq.front().pid)
            {
                Process &p = fiq.front();
                // cout << "fiq" << p.pid << " ";
                if (p.responseTime == -1)
                    p.responseTime = currentTime - p.arrivalTime;

                p.waitingTime--;
                p.Burst.front().second--;
                if (p.Burst.front().second == 0)
                {
                    p.Burst.pop_front();
                    if (p.Burst.size() == 0)
                    {
                        // process completed
                        p.turnaroundTime = currentTime + 1 - p.arrivalTime;
                        p.waitingTime += p.turnaroundTime;
                        processes.push_back(p);
                    }
                    else if (p.Burst.front().first == 'P')
                        fpq.push(p);
                    else
                        foq.push(p);
                    fiq.pop();
                }
            }

            if (!foq.empty() and pid1 != foq.front().pid)
            {
                Process &p = foq.front();
                // cout << "foq" << p.pid << " ";
                if (p.responseTime == -1)
                    p.responseTime = currentTime - p.arrivalTime;

                p.waitingTime--;
                p.Burst.front().second--;
                if (p.Burst.front().second == 0)
                {
                    p.Burst.pop_front();
                    if (p.Burst.size() == 0)
                    {
                        // process completed
                        p.turnaroundTime = currentTime + 1 - p.arrivalTime;
                        p.waitingTime += p.turnaroundTime;
                        processes.push_back(p);
                    }
                    else if (p.Burst.front().first == 'P')
                        fpq.push(p);
                    else
                        fiq.push(p);
                    foq.pop();
                }
            }

            currentTime++;
        }
    }

    void printResult()
    {
        int totalTurnaround = 0;
        int totalResponse = 0;
        int totalWaiting = 0;
        cout << "Scheduling Algorithm FCFS:" << endl;
        cout << "Process ID" << '\t' << "Response Time" << '\t' << "Turnaround Time" << '\t' << "Waiting Time" << endl;
        for (auto &p : processes)
        {
            totalResponse += p.responseTime;
            totalTurnaround += p.turnaroundTime;
            totalWaiting += p.waitingTime;
            cout << p.pid << "\t\t\t\t" << p.responseTime << "\t\t\t\t" << p.turnaroundTime << "\t\t\t" << p.waitingTime << endl;
        }
        cout << "Average Turnaround Time: " << (double)totalTurnaround / processes.size() << endl;
        cout << "Average Response Time: " << (double)totalResponse / processes.size() << endl;
        cout << "Average Waiting Time: " << (double)totalWaiting / processes.size() << endl;
    }
};

int main()
{
    freopen("input.dat", "r", stdin);
    freopen("output.txt", "w", stdout);
    int numOfProcess;
    int quantumValue;
    cin >> numOfProcess >> quantumValue;
    FCFS fcfs(numOfProcess, quantumValue);

    int pid;
    int priority;
    int arrivalTime;

    for (int i = 0; i < numOfProcess; i++)
    {
        cin >> pid >> priority >> arrivalTime;
        Process process(pid, priority, arrivalTime);
        char x;
        int y;
        while (true)
        {
            cin >> x >> y;
            if (x != '-')
            {
                process.takeBurst(x, y);
            }
            else
            {
                break;
            }
        }
        fcfs.addProcess(process);
    }

    fcfs.schedule();
    fcfs.printResult();
    return 0;
}