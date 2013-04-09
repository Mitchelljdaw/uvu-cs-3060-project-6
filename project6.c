// Student: Kory Kehl, Bryson Murray, James Brinkerhoff
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

struct listLink {
   int id;
   int arrival;
   int durration;
   struct listLink * forward;
   struct listLink * back;
};

typedef struct listLink link;

int main(int argc, char * argv[])
{
	link * current;
	link * first;
	link * last;
	
	first = NULL;
	last = NULL;

	double x, y, z;
	int processID[100];
	int arrivalTime[100];
	int timeToCompletion[100];
	int i = 0;
	int incrementLoad = 0;
	
	printf("Students:\n");
	printf("\t-James Brinkerhoff - 10621032\n");
	printf("\t-Bryson Murray - 10501259\n");
	printf("\t-Kory Kehl - 10439952\n");
	printf("Class CS 3060 - Project 6\n");
	
	// Reads in the file
    while (scanf("%lf%lf%lf", &x, &y, &z) == 3)
    {
        processID[incrementLoad] = x;
        arrivalTime[incrementLoad] = y;
        timeToCompletion[incrementLoad] = z;
        ++incrementLoad;
    }
	// Prints for checking
    for(i = 0; i < incrementLoad; ++i)
    {
        printf("%d %d %d\n", processID[i], arrivalTime[i], timeToCompletion[i]);
    }
	//Linked List Creation
    for(i = 0; i < incrementLoad; i++)
    {
    	current = (link *)malloc(sizeof(link));
	current -> id = i+1;
	current -> arrival = arrivalTime[i];
	current -> durration = timeToCompletion[i];	
	current -> back = NULL;
	if(first == NULL){
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
    // finished making linked list

    //displays link list back to front
    /*while(current) {
    	printf("%d-%d-%d\n",current -> id, current -> arrival,current -> durration);
      	current = current->forward ;
    }*/
    link * curr;
    printf("----Linked List Display------\n");
    printf("#-A-D\n");
    curr = first;
    //displays linked list front to back
    while(curr) {
        printf("%d-%d-%d\n",curr -> id, curr -> arrival,curr -> durration);
        curr = curr->back ;
    }

    firstComeFirstServed(first);


 return 0;  
}

void firstComeFirstServed(link * curr){
    printf("----First Come First Serve Display------\n");
    printf("Pid#\tWait\tTurnaround\n");
    printf("---\t----\t----------\n");

    int totalTime = 0;
  
    while(curr) {
	int wait = 0;
	if((totalTime - curr->arrival) > 0)
	{
	    wait = totalTime - curr -> arrival;
	}
	totalTime = totalTime + curr -> durration;	
        int turnaround = wait + curr -> durration;		
	printf("%d\t%d\t%d\n",curr -> id, wait,turnaround);
        curr = curr->back ;
    }
}

