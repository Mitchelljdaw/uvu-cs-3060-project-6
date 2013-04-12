// Student: Kory Kehl
// Instructor: John Jolly
// Class: CS 3060-001
// Project: 6
// Date: Apr 3, 2013
// Description: 

#include <stdio.h>
#include <stdbool.h>

// firstComeFirstServed
// Description: A non-preemtive scheduling algorithm.
// Return: none
// Paramaters: none
void firstComeFirstServed();

// shortestJobFirst
// Description: A non-preemtive scheduling algorithm.
// Return: none
// Paramaters: none
void shortestJobFirst();

// shortestRemainingTimeNext
// Description: A preemtive version of the shortest
//              job first algorithm.
// Return: none
// Paramaters: none
void shortestRemainingTimeNext();

// roundRobin
// Description: A preemtive scheduling algorithm. jobs
//              are stored in a FCFS queue.
// Return: none
// Paramaters: none
void roundRobin();

int processTheProcess(int);
int nextProcess();
int nextprocessR(int);

struct listLink {
    int id;
    int arrival;
    int durration;
    struct listLink * forward;
    struct listLink * back;
};

typedef struct listLink link;

struct proc
{
    int id;
    int arrival;
	int burst;
    int start;
	int rem;
	int wait;
	int finish;
	int turnaround;
    int ti;
	float ratio;
}process[100];

int no;
struct proc temp;
int incrementLoad = 1;

int i, j, k, t = 4, time = 0, n;

int main(int argc, char * argv[])
{
	link * current;
	link * first;
	link * last;
	
	first = NULL;
	last = NULL;
    
	double x, y, z;
	
	printf("Students:\n");
	printf("\t-James Brinkerhoff - 10621032\n");
	printf("\t-Bryson Murray - 10501259\n");
	printf("\t-Kory Kehl - 10439952\n");
	printf("Class CS 3060 - Project 6\n");
	
	// Reads in the file
    while (scanf("%lf%lf%lf", &x, &y, &z) == 3)
    {
        process[incrementLoad].id = x;
        process[incrementLoad].arrival = y;
        process[incrementLoad].burst = z;
        process[incrementLoad].rem = process[incrementLoad].burst;
        process[incrementLoad].ti=0;
		process[incrementLoad].wait=0;
		process[incrementLoad].finish=0;
        ++incrementLoad;
    }
 	n = incrementLoad - 1;
    
	//Linked List Creation
    for(i = 1; i <= n; i++)
    {
    	current = (link *)malloc(sizeof(link));
        current -> id = i;
        current -> arrival = process[i].arrival;
        current -> durration = process[i].burst;
        current -> back = NULL;
        if(first == NULL) {
            current -> forward = NULL;
            first = current;
        }
        else
        {
            current -> forward = last;
        }
        if(last == NULL)
        {
            last = current;
        }
        else
        {
            last -> back = current;
            last = current;
        }
    }
    
    firstComeFirstServed(first);
    shortestJobFirst();
    shortestRemainingTimeNext();
    roundRobin();
    
    return 0;
}

void firstComeFirstServed(link * curr)
{
    printf("\n----First Come First Serve------\n");
    printf("Pid#\tWait\tTurnaround\n");
    printf("---\t\t----\t----------\n");
    
    int totalTime = 0;
    
    while(curr) {
        int wait = 0;
        if((totalTime - curr->arrival) > 0)
        {
            wait = totalTime - curr -> arrival;
        }
        totalTime = totalTime + curr -> durration;	
        int turnaround = wait + curr -> durration;		
        printf("%d\t\t%d\t\t%d\n",curr -> id, wait,turnaround);
        curr = curr->back ;
    }
}

void shortestJobFirst()
{
    process[1].start = process[1].arrival;
    
	while(processTheProcess(n) == 1)
	{
		if(process[no + 1].arrival == time)
			no++;
        
		if(process[j].rem != 0)
		{
			process[j].rem--;
			for(i = 1; i <= no; i++)
			{
				if(i != j && process[i].rem != 0)
					process[i].wait++;
			}
		}
		else
		{
            
			process[j].finish = time;
			j = nextProcess();
			time--;
			process[j].start = time + 1;
		}
        
		time++;
	}
	process[j].finish = time;
    
    printf("\n----Shortest Job First------\n");
    printf("Pid#\tWait\tTurnaround\n");
    printf("---\t\t----\t----------\n");
    
	for(i = 1; i <= n; i++)
	{
        
		process[i].turnaround = process[i].wait + process[i].burst;        
        printf("%d\t\t%d\t\t%d\n", process[i].id, process[i].wait, process[i].turnaround);
        
	}
}

void shortestRemainingTimeNext()
{
    for(i = 1; i <= n; i++)
	{
		for(j = i + 1; j <= n; j++)
		{
			if(process[i].arrival > process[j].arrival)
			{
				temp = process[i];
				process[i] = process[j];
				process[j] = temp;
			}
		}
	}
    
	no = 0;
	j = 1;
    
    
	while(processTheProcess(n) == 1)
	{
		if(process[no + 1].arrival == time)
		{
			no++;
			if(process[j].rem==0)
			    process[j].finish=time;
			j = nextProcess();
		}
        
		if(process[j].rem != 0)
		{
			process[j].rem--;
			for(i = 1; i <= no; i++)
			{
				if(i != j && process[i].rem != 0)
					process[i].wait++;
			}
		}
		else
		{
            
			process[j].finish = time;
			j=nextProcess();
			time--;
			k=j;
            
		}
        
		time++;
	}
	process[k].finish = time;

    
	printf("\n\n----Shortest Remaining Time Next------");
    printf("\nPid#\tWait\tTurnaround\n");
    printf("---\t\t----\t----------\n");
    
    
	for(i = 1; i <= n; i++)
	{        
		process[i].turnaround = process[i].wait + process[i].burst;
        
		printf("%5d %10d %9d ", process[i].id,
               process[i].wait,
               process[i].turnaround);
        
		printf("\n");
	}
}

void roundRobin()
{
    for(i = 1; i <= n; i++)
	{
		for(j = i + 1; j <= n; j++)
		{
			if(process[i].arrival > process[j].arrival)
			{
				temp = process[i];
				process[i] = process[j];
				process[j] = temp;
			}
		}
	}
    
    no = 0;
	j = 1;
    
	while(processTheProcess(n) == 1)
	{
        
		if(process[no + 1].arrival == time)
			no++;
        
		if((process[j].ti<=t)&&(process[j].rem !=0))
		{
			process[j].rem--;
			process[j].ti++;
            
			for(i = 1; i <= no; i++)
			{
				if((i!=j) && (process[i].rem != 0))
					process[i].wait++;
			}
		}
        
        
		if(process[j].rem==0)
			process[j].finish=time;
        
		if((process[j].ti >= t)||(process[j].rem==0))
		{
            
			process[j].ti = 0;
			j=lastProcess(j);
		}
        time++;
        
	}
	process[n].finish = time;
    
	printf("\n\n---ROUND ROBIN SCHEDULING---");
    printf("\nPid#\tWait\tTurnaround\n");
    printf("---\t\t----\t----------\n");
    
    
	for(i = 1; i <= n; i++)
	{
		process[i].turnaround = (process[i].wait-1) + process[i].burst;
        
		printf("%5d %10d %9d ", process[i].id,
               process[i].wait - 1,
               process[i].turnaround);
        
		printf("\n");
	}
}

int processTheProcess(int s)
{
	int i;
	for(i = 1; i <= s; i++)
	{
		if(process[i].rem != 0)
			return 1;
	}
	return 0;
}

int nextProcess()
{
	int min, l, i;
	min = 32000;
	for(i = 1; i <= no; i++)
	{
		if( process[i].rem!=0 && process[i].rem < min)
		{
			min = process[i].rem;
			l = i;
		}
	}
	return l;
}

int lastProcess(int k)
{
	int i;
    
	i=k+1;
    
	while(processTheProcess(i) && i!=k)
        
    {
		if(process[i].rem != 0)
            
			return(i);
		else
			i=(i+1)%no;
	}
}

