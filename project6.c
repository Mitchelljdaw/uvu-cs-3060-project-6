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

int main(int argc, char * argv[])
{
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
	
 return 0;  
}
