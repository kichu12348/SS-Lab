#include <stdio.h>

/*
    shortest job first


    1. The process with the smallest execution time is selected for execution.
    2. If two processes have the same execution time, the process that arrived first is selected.
    3. The process that arrives first, gets added to the queue first, and runs first.
    4. The process that arrives next, gets added to the queue next, and runs next.
    5. The process that arrives last, gets added to the queue last, and runs last.
     this is non-preemptive
    i will use an array of structs called process
    each struct will have an id, arrival time, burst time, waiting time, and turnaround time and completed default 0 ie false

    then i will calculate the waiting time and turnaround time for each process
*/

// struct to hold process information
typedef struct
{
    int id;  // process id
    int at;  // arrival time
    int bt;  // burst time
    int wt;  // waiting time
    int tat; // turnaround time
    int completed;
} Process;

int hasCompleted = 0;
int time = 0;

// function to calculate waiting time and turnaround time

void runProcess(Process p[], int n)
{
    // calculate waiting time and turnaround time for each process
    while (hasCompleted != n)
    {
        int min = 9999;
        int idx=-1;
        for (int i = 0; i < n; i++){
            if(
                !p[i].completed && 
                p[i].at <= time &&
                p[i].bt < min
            ){
                min = p[i].bt;
                idx = i;
            }
        }
        if(idx == -1){
            time++;
            continue;
        }
        p[idx].wt = time - p[idx].at;
        time += p[idx].bt;
        p[idx].tat = time - p[idx].at;
        p[idx].completed = 1;
        hasCompleted++;
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
        p[i].completed = 0;
    }
    runProcess(p, n);
    print(p, n);
    return 0;
}