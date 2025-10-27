#include <stdio.h>

/*
first come first serve

1. The process that arrives first, gets 
   added to the queue first, and runs first.
2. The process that arrives next, gets
   added to the queue next, and runs next.
3. The process that arrives last, gets
    added to the queue last, and runs last.

i will use an array of structs called process
each struct will have an id, arrival time, burst time, waiting time, and turnaround time
i will sort the array of structs by arrival time
then i will calculate the waiting time and turnaround time for each process
*/

// struct to hold process information
typedef  struct
{
    int id; // process id
    int at;// arrival time
    int bt;// burst time
    int wt;// waiting time
    int tat;// turnaround time
} Process;

int time = 0;

// function to sort the array of structs by arrival time using bubble sort
void sort(Process p[], int n)
{
    Process temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].at > p[j].at)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}


// function to calculate waiting time and turnaround time

void runProcess(Process p[], int n)
{
    // calculate waiting time and turnaround time for each process
    for (int i = 0; i < n; i++)
    {
        if (time < p[i].at)  time = p[i].at;
        
        p[i].wt = time - p[i].at;
        p[i].tat = p[i].wt + p[i].bt;
        time += p[i].bt;
    }
}


// function to print the waiting time and turnaround time for each process

void print(Process p[], int n)
{
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].wt, p[i].tat);
    }
}


int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter the arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].id = i + 1;
    }
    sort(p, n);
    runProcess(p, n);
    print(p, n);
    return 0;
}