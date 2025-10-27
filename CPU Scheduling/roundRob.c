#include <stdio.h>


/*
just make sure you use a circular queue 💀 linear is meeehhhh

round robin scheduling
*/

typedef struct
{
    int id;  // Process ID
    int at;  // Arrival Time
    int bt;  // Burst Time (Original)
    int rt;  // Remaining Time (for preemption)
    int wt;  // Waiting Time
    int tat; // Turnaround Time
} Process;

void roundRobin(Process p[], int n, int timeQuantum)
{
    int queue[n], front = 0, rear = 0;
    int time = 0, completed = 0;
    int visited[n];

    // init everything to 0
    for (int i = 0; i < n; i++)
    {
        p[i].rt = p[i].bt;
        p[i].wt = 0;
        p[i].tat = 0;
        visited[i] = 0;
    }

    // add first process to queue
    int first = 0;
    for (int i = 0; i < n; i++)
        if (p[i].at < p[first].at)
            first = i;

    queue[rear++] = first;
    visited[first] = 1;

    while (completed < n)
    {
        int idx = queue[front];
        front = (front + 1) % n;

        int execTime = (p[idx].rt < timeQuantum) ? p[idx].rt : timeQuantum;
        p[idx].rt -= execTime;
        time += execTime;

        if (p[idx].rt == 0)
        {
            p[idx].tat = time - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
        }

        // adds newly arrived processes to queue
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && p[i].at <= time && p[i].rt > 0)
            {
                queue[rear] = i;
                rear = (rear + 1) % n;
                visited[i] = 1;
            }
        }

        // adds the current process to the end of the queue if not completed
        if (p[idx].rt != 0){
            queue[rear] = idx;
            rear = (rear + 1) % n;
        }
    }
}

// Function to print results
void print(Process p[], int n)
{
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].wt, p[i].tat);
    }
}

void main()
{
    int n, timeQuantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process p[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        p[i].id = i + 1;
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    roundRobin(p, n, timeQuantum);
    print(p, n);
}
