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
class PS
{
    class myComp
    {
    public:
        bool operator()(Process &a, Process &b)
        {
            return a.priority > b.priority;
        }
    };
    int numOfProcess;
    int quantumValue;
    int currentTime;
    vector<Process> processes;
    queue<Process> queue;
    priority_queue<Process, vector<Process>, myComp> PQ;
    priority_queue<Process, vector<Process>, myComp> IQ;
    priority_queue<Process, vector<Process>, myComp> OQ;

public:
    PS(int numOfProcess, int quantumValue)
    {
        this->numOfProcess = numOfProcess;
        this->quantumValue = quantumValue;
        currentTime = 0;
    }

    void addProcess(Process p)
    {
        queue.push(p);
    }

    void schedule()
    {
        int currentTime = queue.front().arrivalTime;

        while (PQ.size() || IQ.size() || OQ.size() || !queue.empty())
        {
            if (!queue.empty() and currentTime == queue.front().arrivalTime)
            {
                PQ.push(queue.front());
                queue.pop();
            }

            // cout << endl
            //      << currentTime << "-" << currentTime + 1 << "->";

            Process p2, p3;
            if (!IQ.empty())
                p2 = IQ.top();
            if (!OQ.empty())
                p3 = OQ.top();

            if (!PQ.empty())
            {
                Process p = PQ.top();
                PQ.pop();

                // cout << "PQ" << p.pid << " ";
                if (p.responseTime == -1)
                    p.responseTime = currentTime - p.arrivalTime;

                p.waitingTime--;
                auto pair = p.Burst.front();
                p.Burst.pop_front();

                if (pair.second == 1)
                {
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
                    p.Burst.push_front({pair.first, pair.second - 1});
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

                p.waitingTime--;

                auto pair = p.Burst.front();
                p.Burst.pop_front();

                if (pair.second == 1)
                {
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
                    p.Burst.push_front({pair.first, pair.second - 1});
                    IQ.push(p);
                }
            }

            if (p3.pid != -1)
            {
                Process p = p3;
                OQ.pop();
                // cout << "OQ" << p.pid << " ";
                if (p.responseTime == -1)
                    p.responseTime = currentTime - p.arrivalTime;

                p.waitingTime--;
                auto pair = p.Burst.front();
                p.Burst.pop_front();

                if (pair.second == 1)
                {
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
                    p.Burst.push_front({pair.first, pair.second - 1});
                    OQ.push(p);
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
    PS ps(numOfProcess, quantumValue);

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
        ps.addProcess(process);
    }

    ps.schedule();
    ps.printResult();
    return 0;
}