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

// priority scheduling pre-emptive
class RR
{
    int numOfProcess;
    int quantumValue;
    int currentTime;
    vector<Process> processes;
    queue<Process> readyq;
    queue<Process> PQ;
    queue<Process> IQ;
    queue<Process> OQ;

public:
    RR(int numOfProcess, int quantumValue)
    {
        this->numOfProcess = numOfProcess;
        this->quantumValue = quantumValue;
        currentTime = 0;
    }

    void addProcess(Process p)
    {
        readyq.push(p);
    }

    void schedule()
    {
        while (PQ.size() || IQ.size() || OQ.size() || !readyq.empty())
        {
            while (!readyq.empty() and currentTime >= readyq.front().arrivalTime)
            {
                PQ.push(readyq.front());
                readyq.pop();
            }

            // cout << endl
            //      << currentTime << "-" << currentTime + quantumValue << "->";

            Process p2, p3;
            if (!IQ.empty())
                p2 = IQ.front();
            if (!OQ.empty())
                p3 = OQ.front();

            if (!PQ.empty())
            {
                Process p = PQ.front();
                PQ.pop();

                // cout << "PQ" << p.pid << " ";
                if (p.responseTime == -1)
                    p.responseTime = currentTime - p.arrivalTime;

                auto pair = p.Burst.front();
                p.Burst.pop_front();

                if (pair.second <= quantumValue)
                {
                    p.waitingTime -= (quantumValue - pair.second);
                    if (p.Burst.size() == 0)
                    {
                        // process completed
                        p.turnaroundTime = currentTime + 1 - p.arrivalTime;
                        p.waitingTime += p.turnaroundTime;
                        processes.push_back(p);
                    }
                    else if (p.Burst.front().first == 'I')
                        IQ.push(p);
                    else
                        OQ.push(p);
                }
                else
                {
                    p.waitingTime -= quantumValue;
                    p.Burst.push_front({pair.first, pair.second - quantumValue});
                    PQ.push(p);
                }
            }

            if (p2.pid != -1)
            {
                Process p = p2;
                IQ.pop();

                // cout << "IQ" << p.pid << " ";
                if (p.responseTime == -1)
                    p.responseTime = currentTime - p.arrivalTime;

                auto pair = p.Burst.front();
                p.Burst.pop_front();

                if (pair.second == 1)
                {
                    p.waitingTime -= (quantumValue - pair.second);
                    if (p.Burst.size() == 0)
                    {
                        // process completed
                        p.turnaroundTime = currentTime + 1 - p.arrivalTime;
                        p.waitingTime += p.turnaroundTime;
                        processes.push_back(p);
                    }
                    else if (p.Burst.front().first == 'P')
                        PQ.push(p);
                    else
                        OQ.push(p);
                }
                else
                {
                    p.waitingTime -= quantumValue;
                    p.Burst.push_front({pair.first, pair.second - quantumValue});
                    PQ.push(p);
                }
            }

            if (p3.pid != -1)
            {
                Process p = p3;
                OQ.pop();
                // cout << "OQ" << p.pid << " ";
                if (p.responseTime == -1)
                    p.responseTime = currentTime - p.arrivalTime;

                auto pair = p.Burst.front();
                p.Burst.pop_front();

                if (pair.second == 1)
                {
                    p.waitingTime -= (quantumValue - pair.second);
                    if (p.Burst.size() == 0)
                    {
                        // process completed
                        p.turnaroundTime = currentTime + 1 - p.arrivalTime;
                        p.waitingTime += p.turnaroundTime;
                        processes.push_back(p);
                    }
                    else if (p.Burst.front().first == 'P')
                        PQ.push(p);
                    else
                        IQ.push(p);
                }
                else
                {
                    p.waitingTime -= quantumValue;
                    p.Burst.push_front({pair.first, pair.second - quantumValue});
                    PQ.push(p);
                }
            }

            currentTime += quantumValue;
        }
    }

    void printResult()
    {
        int totalTurnaround = 0;
        int totalResponse = 0;
        int totalWaiting = 0;

        cout << "\nProcess ID" << '\t' << "Response Time" << '\t' << "Turnaround Time" << '\t' << "Waiting Time" << endl;
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
    RR rr(numOfProcess, quantumValue);

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
        rr.addProcess(process);
    }

    rr.schedule();
    rr.printResult();
    return 0;
}